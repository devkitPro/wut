#include <algorithm>
#include <excmd.h>
#include <format.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <zlib.h>
#include "elf.h"

struct Section
{
   elf::SectionHeader header;
   std::vector<char> data;
};

struct RplInfo
{
   std::set<std::string> funcExports;
   std::set<std::string> dataExports;
};

struct ExportsInfo
{
   std::set<std::string> funcExports;
   std::set<std::string> dataExports;
};

static bool
readSection(std::ifstream &fh,
            elf::SectionHeader &header,
            std::vector<char> &data)
{
   // Read section header
   fh.read(reinterpret_cast<char*>(&header), sizeof(elf::SectionHeader));

   if (header.type == elf::SHT_NOBITS || !header.size) {
      return true;
   }

   // Read section data
   if (header.flags & elf::SHF_DEFLATED) {
      auto stream = z_stream {};
      auto ret = Z_OK;

      // Read the original size
      fh.seekg(header.offset.value());
      be_val<uint32_t> size = 0;
      fh.read(reinterpret_cast<char *>(&size), sizeof(uint32_t));
      data.resize(size);

      // Inflate
      memset(&stream, 0, sizeof(stream));
      stream.zalloc = Z_NULL;
      stream.zfree = Z_NULL;
      stream.opaque = Z_NULL;

      ret = inflateInit(&stream);

      if (ret != Z_OK) {
         std::cout << "Couldn't decompress .rpx section because inflateInit returned " << ret << std::endl;
         data.clear();
         return false;
      } else {
         std::vector<char> temp;
         temp.resize(header.size - sizeof(uint32_t));
         fh.read(temp.data(), temp.size());

         stream.avail_in = header.size;
         stream.next_in = reinterpret_cast<Bytef*>(temp.data());
         stream.avail_out = static_cast<uInt>(data.size());
         stream.next_out = reinterpret_cast<Bytef*>(data.data());

         ret = inflate(&stream, Z_FINISH);

         if (ret != Z_OK && ret != Z_STREAM_END) {
            std::cout << "Couldn't decompress .rpx section because inflate returned " << ret << std::endl;
            data.clear();
            return false;
         }

         inflateEnd(&stream);
      }
   } else {
      data.resize(header.size);
      fh.seekg(header.offset.value());
      fh.read(data.data(), header.size);
   }

   return true;
}

static void
readExports(RplInfo &info, const Section &section)
{
   auto exports = reinterpret_cast<const elf::RplExport *>(section.data.data());
   auto strTab = section.data.data();

   for (auto i = 0u; i < exports->count; ++i) {
      // TLS exports have the high bit set in name for some unknown reason...
      auto name = strTab + (exports->exports[i].name & 0x7FFFFFFF);
      auto value = exports->exports[i].value;

      if (value >= 0x10000000) {
         info.dataExports.insert(name);
      } else {
         info.funcExports.insert(name);
      }
   }
}

static bool
readRPL(RplInfo &info, std::ifstream &fh)
{
   elf::Header header;
   fh.read(reinterpret_cast<char*>(&header), sizeof(elf::Header));

   if (header.magic != elf::HeaderMagic) {
      std::cout << "Invalid ELF magic header" << std::endl;
      return false;
   }

   // Read sections
   auto sections = std::vector<Section> {};

   for (auto i = 0u; i < header.shnum; ++i) {
      Section section;
      fh.seekg(header.shoff + header.shentsize * i);

      if (!readSection(fh, section.header, section.data)) {
         std::cout << "Error reading section " << i << std::endl;
         return false;
      }

      sections.push_back(section);
   }

   // Find strtab
   //auto shStrTab = reinterpret_cast<const char *>(sections[header.shstrndx].data.data());

   // Print section data
   for (auto i = 0u; i < sections.size(); ++i) {
      auto &section = sections[i];

      if (section.header.type == elf::SHT_RPL_EXPORTS) {
         readExports(info, section);
      }
   }

   return true;
}

static bool
readTextExports(ExportsInfo &info, std::ifstream &fh)
{
   std::string line;

   while (std::getline(fh, line)) {
      if (line.find("EXPORT(") == 0) {
         auto name = line.substr(strlen("EXPORT("));
         name = name.erase(name.find(')'), 2);
         info.funcExports.insert(name);
      }
   }

   return true;
}

int main(int argc, char **argv)
{
   excmd::parser parser;
   excmd::option_state options;
   using excmd::description;
   using excmd::value;

   try {
      parser.global_options()
         .add_option("H,help",
                     description { "Show help." })
         .add_option("f,functions",
                     description { "Print unimplemented function exports." })
         .add_option("d,data",
                     description { "Print unimplemented data exports." });

      parser.default_command()
         .add_argument("rpl-path",
                       description { "Path to RPL file" },
                       value<std::string> {})
         .add_argument("exports-path",
                       description { "Path to exports.h file" },
                       value<std::string> {});

      options = parser.parse(argc, argv);
   } catch (excmd::exception ex) {
      std::cout << "Error parsing options: " << ex.what() << std::endl;
      return -1;
   }

   if (options.empty() || options.has("help") || !options.has("rpl-path") || !options.has("exports-path")) {
      std::cout << argv[0] << " rpl-path exports-path" << std::endl;
      std::cout << parser.format_help(argv[0]);
      return 0;
   }

   auto rplPath = options.get<std::string>("rpl-path");
   auto exportsPath = options.get<std::string>("exports-path");

   // Read RPL
   std::ifstream fh { rplPath, std::ifstream::binary };

   if (!fh.is_open()) {
      std::cout << "Could not open " << rplPath << " for reading" << std::endl;
      return -1;
   }

   RplInfo rplInfo;

   if (!readRPL(rplInfo, fh)) {
      std::cout << "Error reading " << rplPath << std::endl;
      return -1;
   }

   fh.close();

   // Read exports
   fh.open(exportsPath, std::ifstream::in);

   if (!fh.is_open()) {
      std::cout << "Could not open " << exportsPath << " for reading" << std::endl;
      return -1;
   }

   ExportsInfo exportsInfo;

   if (!readTextExports(exportsInfo, fh)) {
      std::cout << "Error reading " << exportsPath << std::endl;
      return -1;
   }

   fh.close();

   // Check that we do not have any extra exports which are not exported from RPL.
   std::set<std::string> funcUnion, extraExports;
   int result = 0;

   std::set_union(rplInfo.funcExports.begin(), rplInfo.funcExports.end(),
                  exportsInfo.funcExports.begin(), exportsInfo.funcExports.end(),
                  std::inserter(funcUnion, funcUnion.begin()));

   std::set_difference(funcUnion.begin(), funcUnion.end(),
                       rplInfo.funcExports.begin(), rplInfo.funcExports.end(),
                       std::inserter(extraExports, extraExports.begin()));

   if (!extraExports.empty()) {
      std::cout << "Error: Exports found in exports.h which do not exist in rpl:" << std::endl;

      for (auto &name : extraExports) {
         std::cout << " - " << name << std::endl;
      }

      std::cout << std::endl;
      result = -1;
   }

   if (options.has("functions")) {
      // Print implemented function exports
      std::set<std::string> intersection;

      std::set_intersection(rplInfo.funcExports.begin(), rplInfo.funcExports.end(),
                            exportsInfo.funcExports.begin(), exportsInfo.funcExports.end(),
                            std::inserter(intersection, intersection.begin()));

      if (!intersection.empty()) {
         std::cout << "Implemented function exports:" << std::endl;

         for (auto &name : intersection) {
            std::cout << " - " << name << std::endl;
         }

         std::cout << std::endl;
      }

      // Print unimplemented function exports
      std::set<std::string> difference;

      std::set_difference(rplInfo.funcExports.begin(), rplInfo.funcExports.end(),
                          exportsInfo.funcExports.begin(), exportsInfo.funcExports.end(),
                          std::inserter(difference, difference.begin()));

      if (!difference.empty()) {
         std::cout << "Unimplemented function exports:" << std::endl;

         for (auto &name : difference) {
            std::cout << " - " << name << std::endl;
         }

         std::cout << std::endl;
      }
   }

   if (options.has("data")) {
      // Print implemented data exports
      std::set<std::string> intersection;

      std::set_intersection(rplInfo.dataExports.begin(), rplInfo.dataExports.end(),
                            exportsInfo.dataExports.begin(), exportsInfo.dataExports.end(),
                            std::inserter(intersection, intersection.begin()));

      if (!intersection.empty()) {
         std::cout << "Implemented data exports:" << std::endl;

         for (auto &name : intersection) {
            std::cout << " - " << name << std::endl;
         }

         std::cout << std::endl;
      }

      // Print unimplemented data exports
      std::set<std::string> difference;

      std::set_difference(rplInfo.dataExports.begin(), rplInfo.dataExports.end(),
                          exportsInfo.dataExports.begin(), exportsInfo.dataExports.end(),
                          std::inserter(difference, difference.begin()));

      if (!difference.empty()) {
         std::cout << "Unimplemented data exports:" << std::endl;

         for (auto &name : difference) {
            std::cout << " - " << name << std::endl;
         }

         std::cout << std::endl;
      }
   }

   return result;
}
