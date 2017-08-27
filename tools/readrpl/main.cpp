#include <excmd.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <zlib.h>
#include "elf.h"

struct Section
{
   elf::SectionHeader header;
   std::vector<char> data;
};

static std::string
formatET(uint32_t type)
{
   switch (type) {
   case elf::ET_NONE:
      return "ET_NONE";
   case elf::ET_REL:
      return "ET_REL";
   case elf::ET_EXEC:
      return "ET_EXEC";
   case elf::ET_DYN:
      return "ET_DYN";
   case elf::ET_CORE:
      return "ET_CORE";
   case elf::ET_CAFE_RPL:
      return "ET_CAFE_RPL";
   default:
      return "";
   }
}

static std::string
formatEM(uint32_t machine)
{
   switch (machine) {
   case elf::EM_PPC:
      return "EM_PPC";
   default:
      return "";
   }
}

static std::string
formatEABI(uint32_t machine)
{
   switch (machine) {
   case elf::EABI_CAFE:
      return "EABI_CAFE";
   default:
      return "";
   }
}

static std::string
formatSHF(uint32_t flags)
{
   std::string result = "";

   if (flags & elf::SHF_WRITE) {
      result += "W";
   }

   if (flags & elf::SHF_ALLOC) {
      result += "A";
   }

   if (flags & elf::SHF_EXECINSTR) {
      result += "X";
   }

   if (flags & elf::SHF_DEFLATED) {
      result += "Z";
   }

   return result;
}

static std::string
formatSHT(uint32_t type)
{
   switch (type) {
   case elf::SHT_NULL:
      return "SHT_NULL";
   case elf::SHT_PROGBITS:
      return "SHT_PROGBITS";
   case elf::SHT_SYMTAB:
      return "SHT_SYMTAB";
   case elf::SHT_STRTAB:
      return "SHT_STRTAB";
   case elf::SHT_RELA:
      return "SHT_RELA";
   case elf::SHT_HASH:
      return "SHT_HASH";
   case elf::SHT_DYNAMIC:
      return "SHT_DYNAMIC";
   case elf::SHT_NOTE:
      return "SHT_NOTE";
   case elf::SHT_NOBITS:
      return "SHT_NOBITS";
   case elf::SHT_REL:
      return "SHT_REL";
   case elf::SHT_SHLIB:
      return "SHT_SHLIB";
   case elf::SHT_DYNSYM:
      return "SHT_DYNSYM";
   case elf::SHT_INIT_ARRAY:
      return "SHT_INIT_ARRAY";
   case elf::SHT_FINI_ARRAY:
      return "SHT_FINI_ARRAY";
   case elf::SHT_PREINIT_ARRAY:
      return "SHT_PREINIT_ARRAY";
   case elf::SHT_GROUP:
      return "SHT_GROUP";
   case elf::SHT_SYMTAB_SHNDX:
      return "SHT_SYMTAB_SHNDX";
   case elf::SHT_LOPROC:
      return "SHT_LOPROC";
   case elf::SHT_HIPROC:
      return "SHT_HIPROC";
   case elf::SHT_LOUSER:
      return "SHT_LOUSER";
   case elf::SHT_RPL_EXPORTS:
      return "SHT_RPL_EXPORTS";
   case elf::SHT_RPL_IMPORTS:
      return "SHT_RPL_IMPORTS";
   case elf::SHT_RPL_CRCS:
      return "SHT_RPL_CRCS";
   case elf::SHT_RPL_FILEINFO:
      return "SHT_RPL_FILEINFO";
   case elf::SHT_HIUSER:
      return "SHT_HIUSER";
   default:
      return fmt::format("__UNK_{:08X}", type);
   }
}

static std::string
formatHeader(elf::Header &header)
{
   fmt::MemoryWriter out;
   out.write("ElfHeader\n");
   out.write("  magic = 0x{:08X}\n", header.magic);
   out.write("  fileClass = {}\n", static_cast<unsigned>(header.fileClass));
   out.write("  encoding = {}\n", static_cast<unsigned>(header.encoding));
   out.write("  elfVersion = {}\n", static_cast<unsigned>(header.elfVersion));
   out.write("  abi = {} 0x{:04x}\n", formatEABI(header.abi), header.abi);

   out.write("  type = {} 0x{:04X}\n", formatET(header.type), header.type);
   out.write("  machine = {} {}\n", formatEM(header.machine), header.machine);
   out.write("  version = 0x{:X}\n", header.version);
   out.write("  entry = 0x{:08X}\n", static_cast<uint32_t>(header.entry));
   out.write("  phoff = 0x{:X}\n", header.phoff);
   out.write("  shoff = 0x{:X}\n", header.shoff);
   out.write("  flags = 0x{:X}\n", header.flags);
   out.write("  ehsize = {}\n", header.ehsize);
   out.write("  phentsize = {}\n", header.phentsize);
   out.write("  phnum = {}\n", header.phnum);
   out.write("  shentsize = {}\n", header.shentsize);
   out.write("  shnum = {}\n", header.shnum);
   out.write("  shstrndx = {}\n", header.shstrndx);

   return out.str();
}

static std::string
formatSectionSummary(std::vector<Section> &sections, const char *shStrTab)
{
   fmt::MemoryWriter out;
   out.write("Sections:\n");
   out.write("  {:<4} {:<20} {:<16} {:<8} {:<6} {:<6} {:<2} {:<4} {:<2} {:<4} {:<5}\n",
             "[Nr]", "Name", "Type", "Addr", "Off", "Size", "ES", "Flag", "Lk", "Info", "Align");

   for (auto i = 0u; i < sections.size(); ++i) {
      auto &section = sections[i];
      auto name = shStrTab + section.header.name;
      auto type = formatSHT(section.header.type);
      auto flags = formatSHF(section.header.flags);

      out.write("  [{:>2}] {:<20} {:<16} {:08X} {:06X} {:06X} {:02X} {:>4} {:>2} {:>4} {:>5}\n",
                i,
                name,
                type,
                static_cast<uint32_t>(section.header.addr),
                section.header.offset,
                section.header.size,
                section.header.entsize,
                flags,
                section.header.link,
                section.header.info,
                section.header.addralign);
   }

   return out.str();
}

static void
formatFileInfo(fmt::MemoryWriter &out, Section &section)
{
   auto &info = *reinterpret_cast<elf::RplFileInfo *>(section.data.data());
   auto filename = section.data.data() + info.filename;

   out.write("  version             = 0x{:08X}\n", static_cast<uint32_t>(info.version));
   out.write("  textSize            = 0x{:08X}\n", info.textSize);
   out.write("  textAlign           = 0x{:X}\n", info.textAlign);
   out.write("  dataSize            = 0x{:08X}\n", info.dataSize);
   out.write("  dataAlign           = 0x{:X}\n", info.dataAlign);
   out.write("  loadSize            = 0x{:08X}\n", info.loadSize);
   out.write("  loadAlign           = 0x{:X}\n", info.loadAlign);
   out.write("  tempSize            = 0x{:X}\n", info.tempSize);
   out.write("  trampAdjust         = 0x{:X}\n", info.trampAdjust);
   out.write("  trampAddition       = 0x{:X}\n", info.trampAddition);
   out.write("  sdaBase             = 0x{:08X}\n", info.sdaBase);
   out.write("  sda2Base            = 0x{:08X}\n", info.sda2Base);
   out.write("  stackSize           = 0x{:08X}\n", info.stackSize);
   out.write("  heapSize            = 0x{:08X}\n", info.heapSize);

   if (info.filename) {
      out.write("  filename            = {}\n", filename);
   } else {
      out.write("  filename            = 0\n");
   }

   out.write("  flags               = 0x{:X}\n", info.flags);
   out.write("  minSdkVersion       = 0x{:08X}\n", static_cast<uint32_t>(info.minVersion));
   out.write("  compressionLevel    = {}\n", info.compressionLevel);
   out.write("  fileInfoPad         = 0x{:X}\n", info.fileInfoPad);
   out.write("  sdkVersion          = 0x{:X}\n", info.cafeSdkVersion);
   out.write("  sdkRevision         = 0x{:X}\n", info.cafeSdkRevision);
   out.write("  tlsModuleIndex      = 0x{:X}\n", info.tlsModuleIndex);
   out.write("  tlsAlignShift       = 0x{:X}\n", info.tlsAlignShift);
   out.write("  runtimeFileInfoSize = 0x{:X}\n", info.runtimeFileInfoSize);

   if (info.tagOffset) {
      const char *tags = section.data.data() + info.tagOffset;
      out.write("  Tags:\n");

      while (*tags) {
         auto key = tags;
         tags += strlen(tags) + 1;
         auto value = tags;
         tags += strlen(tags) + 1;

         out.write("    \"{}\" = \"{}\"\n", key, value);
      }
   }
}

static std::string
formatRelType(uint32_t type)
{
   switch (type) {
   case elf::R_PPC_NONE:
      return "NONE";
   case elf::R_PPC_ADDR32:
      return "ADDR32";
   case elf::R_PPC_ADDR24:
      return "ADDR24";
   case elf::R_PPC_ADDR16:
      return "ADDR16";
   case elf::R_PPC_ADDR16_LO:
      return "ADDR16_LO";
   case elf::R_PPC_ADDR16_HI:
      return "ADDR16_HI";
   case elf::R_PPC_ADDR16_HA:
      return "ADDR16_HA";
   case elf::R_PPC_ADDR14:
      return "ADDR14";
   case elf::R_PPC_ADDR14_BRTAKEN:
      return "ADDR14_BRTAKEN";
   case elf::R_PPC_ADDR14_BRNTAKEN:
      return "ADDR14_BRNTAKEN";
   case elf::R_PPC_REL24:
      return "REL24";
   case elf::R_PPC_REL14:
      return "REL14";
   case elf::R_PPC_REL14_BRTAKEN:
      return "REL14_BRTAKEN";
   case elf::R_PPC_REL14_BRNTAKEN:
      return "REL14_BRNTAKEN";
   case elf::R_PPC_GOT16:
      return "GOT16";
   case elf::R_PPC_GOT16_LO:
      return "GOT16_LO";
   case elf::R_PPC_GOT16_HI:
      return "GOT16_HI";
   case elf::R_PPC_GOT16_HA:
      return "GOT16_HA";
   case elf::R_PPC_PLTREL24:
      return "PLTREL24";
   case elf::R_PPC_JMP_SLOT:
      return "JMP_SLOT";
   case elf::R_PPC_RELATIVE:
      return "RELATIVE";
   case elf::R_PPC_LOCAL24PC:
      return "LOCAL24PC";
   case elf::R_PPC_REL32:
      return "REL32";
   case elf::R_PPC_TLS:
      return "TLS";
   case elf::R_PPC_DTPMOD32:
      return "DTPMOD32";
   case elf::R_PPC_TPREL16:
      return "TPREL16";
   case elf::R_PPC_TPREL16_LO:
      return "TPREL16_LO";
   case elf::R_PPC_TPREL16_HI:
      return "TPREL16_HI";
   case elf::R_PPC_TPREL16_HA:
      return "TPREL16_HA";
   case elf::R_PPC_TPREL32:
      return "TPREL32";
   case elf::R_PPC_DTPREL16:
      return "DTPREL16";
   case elf::R_PPC_DTPREL16_LO:
      return "DTPREL16_LO";
   case elf::R_PPC_DTPREL16_HI:
      return "DTPREL16_HI";
   case elf::R_PPC_DTPREL16_HA:
      return "DTPREL16_HA";
   case elf::R_PPC_DTPREL32:
      return "DTPREL32";
   case elf::R_PPC_GOT_TLSGD16:
      return "GOT_TLSGD16";
   case elf::R_PPC_GOT_TLSGD16_LO:
      return "GOT_TLSGD16_LO";
   case elf::R_PPC_GOT_TLSGD16_HI:
      return "GOT_TLSGD16_HI";
   case elf::R_PPC_GOT_TLSGD16_HA:
      return "GOT_TLSGD16_HA";
   case elf::R_PPC_GOT_TLSLD16:
      return "GOT_TLSLD16";
   case elf::R_PPC_GOT_TLSLD16_LO:
      return "GOT_TLSLD16_LO";
   case elf::R_PPC_GOT_TLSLD16_HI:
      return "GOT_TLSLD16_HI";
   case elf::R_PPC_GOT_TLSLD16_HA:
      return "GOT_TLSLD16_HA";
   case elf::R_PPC_GOT_TPREL16:
      return "GOT_TPREL16";
   case elf::R_PPC_GOT_TPREL16_LO:
      return "GOT_TPREL16_LO";
   case elf::R_PPC_GOT_TPREL16_HI:
      return "GOT_TPREL16_HI";
   case elf::R_PPC_GOT_TPREL16_HA:
      return "GOT_TPREL16_HA";
   case elf::R_PPC_GOT_DTPREL16:
      return "GOT_DTPREL16";
   case elf::R_PPC_GOT_DTPREL16_LO:
      return "GOT_DTPREL16_LO";
   case elf::R_PPC_GOT_DTPREL16_HI:
      return "GOT_DTPREL16_HI";
   case elf::R_PPC_GOT_DTPREL16_HA:
      return "GOT_DTPREL16_HA";
   case elf::R_PPC_TLSGD:
      return "TLSGD";
   case elf::R_PPC_TLSLD:
      return "TLSLD";
   case elf::R_PPC_EMB_SDA21:
      return "EMB_SDA21";
   case elf::R_PPC_REL16:
      return "REL16";
   case elf::R_PPC_REL16_LO:
      return "REL16_LO";
   case elf::R_PPC_REL16_HI:
      return "REL16_HI";
   case elf::R_PPC_REL16_HA:
      return "REL16_HA";
   default:
      return fmt::format("__UNK_{:02X}", type);
   }
}

static std::string
formatSymType(uint32_t type)
{
   switch (type) {
   case elf::STT_NOTYPE:
      return "NOTYPE";
   case elf::STT_OBJECT:
      return "OBJECT";
   case elf::STT_FUNC:
      return "FUNC";
   case elf::STT_SECTION:
      return "SECTION";
   case elf::STT_FILE:
      return "FILE";
   case elf::STT_COMMON:
      return "COMMON";
   case elf::STT_TLS:
      return "TLS";
   case elf::STT_LOOS:
      return "LOOS";
   case elf::STT_HIOS:
      return "HIOS";
   case elf::STT_GNU_IFUNC:
      return "GNU_IFUNC";
   default:
      return fmt::format("__UNK_{:02X}", type);
   }
}

static std::string
formatSymBinding(uint32_t type)
{
   switch (type) {
   case elf::STB_LOCAL:
      return "LOCAL";
   case elf::STB_GLOBAL:
      return "GLOBAL";
   case elf::STB_WEAK:
      return "WEAK";
   case elf::STB_GNU_UNIQUE:
      return "UNIQUE";
   default:
      return fmt::format("__UNK_{:02X}", type);
   }
}

static std::string
formatSymShndx(uint32_t type)
{
   switch (type) {
   case elf::SHN_UNDEF:
      return "UND";
   case elf::SHN_ABS:
      return "ABS";
   case elf::SHN_COMMON:
      return "CMN";
   case elf::SHN_XINDEX:
      return "UND";
   default:
      return fmt::format("{}", type);
   }
}

static void
formatRela(fmt::MemoryWriter &out, std::vector<Section> &sections, const char *shStrTab, Section &section)
{
   out.write("  {:<8} {:<8} {:<16} {:<8} {}\n", "Offset", "Info", "Type", "Value", "Name + Addend");

   auto &symSec = sections[section.header.link];
   auto symbols = reinterpret_cast<elf::Symbol *>(symSec.data.data());
   auto &symStrTab = sections[symSec.header.link];

   auto relas = reinterpret_cast<elf::Rela *>(section.data.data());
   auto count = section.data.size() / sizeof(elf::Rela);

   for (auto i = 0u; i < count; ++i) {
      auto &rela = relas[i];

      auto index = rela.info >> 8;
      auto type = rela.info & 0xff;
      auto typeName = formatRelType(type);

      auto symbol = symbols[index];
      auto name = reinterpret_cast<const char*>(symStrTab.data.data()) + symbol.name;

      out.write("  {:08X} {:08X} {:<16} {:08X} {} + {:X}\n",
                static_cast<uint32_t>(rela.offset),
                rela.info,
                typeName,
                static_cast<uint32_t>(symbol.value),
                name,
                static_cast<uint32_t>(rela.addend));
   }
}

static void
formatSymTab(fmt::MemoryWriter &out, std::vector<Section> &sections, Section &section)
{
   auto strTab = reinterpret_cast<const char*>(sections[section.header.link].data.data());

   out.write("  {:<4} {:<8} {:<6} {:<8} {:<8} {:<3} {}\n",
             "Num", "Value", "Size",
             "Type", "Bind",
             "Ndx", "Name");

   auto id = 0u;
   auto symbols = reinterpret_cast<elf::Symbol *>(section.data.data());
   auto count = section.data.size() / sizeof(elf::Symbol);

   for (auto i = 0u; i < count; ++i) {
      auto &symbol = symbols[i];

      auto name = strTab + symbol.name;
      auto binding = symbol.info >> 4;
      auto type = symbol.info & 0xf;
      auto typeName = formatSymType(type);
      auto bindingName = formatSymBinding(binding);
      auto ndx = formatSymShndx(symbol.shndx);

      out.write("  {:>4} {:08X} {:>6} {:<8} {:<8} {:>3} {}\n",
                id, static_cast<uint32_t>(symbol.value), symbol.size, typeName, bindingName, ndx, name);

      ++id;
   }
}

static void
formatRplImports(fmt::MemoryWriter &out, std::vector<Section> &sections, uint32_t index, Section &section)
{
   auto import = reinterpret_cast<elf::RplImport *>(section.data.data());

   out.write("  name = {}\n", import->name);
   out.write("  signature = 0x{:08X}\n", static_cast<uint32_t>(import->signature));
   out.write("  count = {}\n", import->count);

   if (import->count) {
      for (auto &symSection : sections) {
         if (symSection.header.type != elf::SHT_SYMTAB) {
            continue;
         }

         auto symbols = reinterpret_cast<elf::Symbol *>(symSection.data.data());
         auto count = symSection.data.size() / sizeof(elf::Symbol);
         auto strTab = reinterpret_cast<const char*>(sections[symSection.header.link].data.data());

         for (auto i = 0u; i < count; ++i) {
            auto &symbol = symbols[i];

            if (symbol.shndx == index) {
               out.write("    {}\n", strTab + symbol.name);
            }
         }
      }
   }
}

static void
formatRplCrcs(fmt::MemoryWriter &out, std::vector<Section> &sections, const char *shStrTab, Section &section)
{
   auto crcs = reinterpret_cast<elf::RplCrc *>(section.data.data());
   auto count = section.data.size() / sizeof(elf::RplCrc);

   for (auto i = 0u; i < count; ++i) {
      auto name = shStrTab + sections[i].header.name;
      out.write("  [{:>2}] 0x{:08X} {}\n", i, static_cast<uint32_t>(crcs[i].crc), name);
   }
}

static void
formatRplExports(fmt::MemoryWriter &out, Section &section)
{
   auto exports = reinterpret_cast<elf::RplExport *>(section.data.data());
   auto strTab = section.data.data();

   out.write("  signature = 0x{:08X}\n", static_cast<uint32_t>(exports->signature));
   out.write("  count = {}\n", exports->count);

   for (auto i = 0u; i < exports->count; ++i) {
      // TLS exports have the high bit set in name for some unknown reason...
      auto name = strTab + (exports->exports[i].name & 0x7FFFFFFF);
      auto value = exports->exports[i].value;

      out.write("    0x{:08X} {}\n", static_cast<uint32_t>(value), name);
   }
}

bool readSection(std::ifstream &fh, elf::SectionHeader &header, std::vector<char> &data)
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
         temp.resize(header.size-sizeof(uint32_t));
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
         .add_option("a,all",
                     description { "Equivalent to: -h -S -s -r -i -x -c -f" })
         .add_option("h,file-header",
                     description { "Display the ELF file header" })
         .add_option("S,sections",
                     description { "Display the sections' header" })
         .add_option("s,symbols",
                     description { "Display the symbol table" })
         .add_option("r,relocs",
                     description { "Display the relocations" })
         .add_option("i,imports",
                     description { "Display the RPL imports" })
         .add_option("x,exports",
                     description { "Display the RPL exports" })
         .add_option("c,crc",
                     description { "Display the RPL crc" })
         .add_option("f,file-info",
                     description { "Display the RPL file info" });

      parser.default_command()
         .add_argument("path",
                       description { "Path to RPL file" },
                       value<std::string> {});

      options = parser.parse(argc, argv);
   } catch (excmd::exception ex) {
      std::cout << "Error parsing options: " << ex.what() << std::endl;
      return -1;
   }

   if (options.empty() || options.has("help") || !options.has("path")) {
      std::cout << argv[0] << " <options> path" << std::endl;
      std::cout << parser.format_help(argv[0]) << std::endl;
      return 0;
   }

   auto all = options.has("all");

   auto dumpElfHeader = all || options.has("file-header");
   auto dumpSectionSummary = all || options.has("sections");
   auto dumpSectionRela = all || options.has("relocs");
   auto dumpSectionSymtab = all || options.has("symbols");
   auto dumpSectionRplExports = all || options.has("exports");
   auto dumpSectionRplImports = all || options.has("imports");
   auto dumpSectionRplCrcs = all || options.has("crc");
   auto dumpSectionRplFileinfo = all || options.has("file-info");
   auto path = options.get<std::string>("path");

   // If no options are set (other than "path"), let's default to a summary
   if (options.set_options.size() == 1) {
      dumpElfHeader = true;
      dumpSectionSummary = true;
      dumpSectionRplFileinfo = true;
   }

   // Read file
   std::ifstream fh { path, std::ifstream::binary };

   if (!fh.is_open()) {
      std::cout << "Could not open " << path << " for reading" << std::endl;
      return -1;
   }

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
         return -1;
      }

      sections.push_back(section);
   }

   // Find strtab
   auto shStrTab = reinterpret_cast<const char *>(sections[header.shstrndx].data.data());

   // Format shit
   if (dumpElfHeader) {
      std::cout << formatHeader(header) << std::endl;
   }

   if (dumpSectionSummary) {
      std::cout << formatSectionSummary(sections, shStrTab) << std::endl;
   }

   // Print section data
   for (auto i = 0u; i < sections.size(); ++i) {
      fmt::MemoryWriter out;
      auto &section = sections[i];
      auto name = shStrTab + section.header.name;
      out.write("Section {}: {}, {}, {} bytes\n", i, formatSHT(section.header.type), name, section.data.size());

      switch (section.header.type) {
      case elf::SHT_NULL:
      case elf::SHT_NOBITS:
         // Print nothing
         break;
      case elf::SHT_RELA:
         if (!dumpSectionRela) {
            continue;
         }

         formatRela(out, sections, shStrTab, section);
         break;
      case elf::SHT_SYMTAB:
         if (!dumpSectionSymtab) {
            continue;
         }

         formatSymTab(out, sections, section);
         break;
      case elf::SHT_STRTAB:
         break;
      case elf::SHT_PROGBITS:
         break;
      case elf::SHT_RPL_EXPORTS:
         if (!dumpSectionRplExports) {
            continue;
         }

         formatRplExports(out, section);
         break;
      case elf::SHT_RPL_IMPORTS:
         if (!dumpSectionRplImports) {
            continue;
         }

         formatRplImports(out, sections, i, section);
         break;
      case elf::SHT_RPL_CRCS:
         if (!dumpSectionRplCrcs) {
            continue;
         }

         formatRplCrcs(out, sections, shStrTab, section);
         break;
      case elf::SHT_RPL_FILEINFO:
         if (!dumpSectionRplFileinfo) {
            continue;
         }

         formatFileInfo(out, section);
         break;
      }

      std::cout << out.str() << std::endl;
   }

   return 0;
}
