#include "utils.h"

#include <array>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <functional>
#include <fstream>
#include <locale>
#include <vector>
#include <string>
#include <zlib.h>

enum class ReadMode
{
   INVALID,
   TEXT,
   DATA
};

void
writeExports(std::ofstream &out,
             const std::string &moduleName,
             bool isData,
             const std::vector<std::string> &exports)
{
   // Align module name up to 8 bytes
   auto moduleNameSize = (moduleName.length() + 1 + 7) & ~7;

   // Calculate the data block size
   auto exportSecSize = exports.size() * 8;

   if (exportSecSize < moduleNameSize) {
      exportSecSize = moduleNameSize;
   }

   // Calculate export hash
   uint32_t exportsHash = crc32(0, Z_NULL, 0);

   for (auto &exp : exports) {
      exportsHash = crc32(exportsHash, reinterpret_cast<const Bytef *>(exp.data()), exp.size() + 1);
   }

   std::array<Bytef, 0xE> extraHashBytes;
   extraHashBytes.fill(0);
   exportsHash = crc32(exportsHash, extraHashBytes.data(), extraHashBytes.size());

   // Setup section data
   std::vector<uint32_t> secData;
   secData.resize(exportSecSize / 4, 0);
   memcpy(secData.data(), moduleName.c_str(), moduleName.length());

   out << std::endl;

   if (isData) {
      out << ".section .dimport_" << moduleName << ", \"a\", @0x80000002" << std::endl;
   } else {
      out << ".section .fimport_" << moduleName << ", \"ax\", @0x80000002" << std::endl;
   }

   out << ".align 4" << std::endl;
   out << std::endl;

   out << ".long " << exports.size() << std::endl;
   out << ".long 0x" << std::hex << exportsHash << std::endl;
   out << std::endl;

   const char *type = isData ? "@object" : "@function";

   for (auto i = 0; i < exportSecSize / 8; ++i) {
      if (i < exports.size()) {
         out << ".global " << exports[i] << std::endl;
         out << ".type " << exports[i] << ", " << type << std::endl;
         out << exports[i] << ":" << std::endl;
      }

      out << ".long 0x" << std::hex << byte_swap(secData[i * 2 + 0]) << std::endl;
      out << ".long 0x" << std::hex << byte_swap(secData[i * 2 + 1]) << std::endl;
      out << std::endl;
   }
}

int main(int argc, char **argv)
{
   std::string moduleName;
   std::vector<std::string> funcExports, dataExports;
   ReadMode readMode = ReadMode::INVALID;

   if (argc < 3) {
      std::cout << argv[0] << " <exports.def> <output.S>" << std::endl;
      return 0;
   }

   {
      std::ifstream in;
      in.open(argv[1]);

      if (!in.is_open()) {
         std::cout << "Could not open file " << argv[1] << " for reading" << std::endl;
         return -1;
      }

      std::string line;
      while (std::getline(in, line)) {
         // Trim comments
         std::size_t commentOffset = line.find("//");
         if (commentOffset != std::string::npos) {
            line = line.substr(0, commentOffset);
         }

         // Trim whitespace
         line = trim(line);

         // Skip blank lines
         if (line.length() == 0) {
            continue;
         }

         // Look for section headers
         if (line[0] == ':') {
            if (line.substr(1) == "TEXT") {
               readMode = ReadMode::TEXT;
            } else if (line.substr(1) == "DATA") {
               readMode = ReadMode::DATA;
            } else if (line.substr(1, 4) == "NAME") {
               moduleName = line.substr(6);
            } else {
               std::cout << "Unexpected section type" << std::endl;
               return -1;
            }
            continue;
         }

         if (readMode == ReadMode::TEXT) {
            funcExports.push_back(line);
         } else if (readMode == ReadMode::DATA) {
            dataExports.push_back(line);
         } else {
            std::cout << "Unexpected section data" << std::endl;
            return -1;
         }
      }
   }

   {
      std::ofstream out;
      out.open(argv[2]);

      if (!out.is_open()) {
         std::cout << "Could not open file " << argv[2] << " for writing" << std::endl;
         return -1;
      }

      if (funcExports.size() > 0) {
         writeExports(out, moduleName, false, funcExports);
      }

      if (dataExports.size() > 0) {
         writeExports(out, moduleName, true, dataExports);
      }
   }

   return 0;
}
