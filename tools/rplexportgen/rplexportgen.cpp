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

/*
.extern __preinit_user

.section .fexports, "", @0x80000001
.align 4

.long 1
.long 0x13371337

.long __preinit_user
.long 0x10

.string "__preinit_user"
.byte 0
 */

enum class ReadMode
{
   INVALID,
   TEXT,
   DATA
};

void
writeExports(std::ofstream &out,
             bool isData,
             const std::vector<std::string> &exports)
{
   // Calculate signature
   uint32_t signature = crc32(0, Z_NULL, 0);
   for (const auto &name : exports) {
      signature = crc32(signature, reinterpret_cast<const Bytef *>(name.data()), name.size() + 1);
   }

   // Write out .extern to declare the symbols
   for (const auto &name : exports) {
      out << ".extern " << name << std::endl;
   }
   out << std::endl;

   // Write out header
   if (isData) {
      out << ".section .dexports, \"a\", @0x80000001" << std::endl;
   } else {
      out << ".section .fexports, \"ax\", @0x80000001" << std::endl;
   }

   out << ".align 4" << std::endl;
   out << std::endl;

   out << ".long " << exports.size() << std::endl;
   out << ".long 0x" << std::hex << signature << std::endl;
   out << std::endl;

   // Write out each export
   auto nameOffset = 8 + 8 * exports.size();
   for (const auto &name : exports) {
      out << ".long " << name << std::endl;
      out << ".long 0x" << std::hex << nameOffset << std::endl;
      nameOffset += name.size() + 1;
   }
   out << std::endl;

   // Write out the strings
   for (const auto &name : exports) {
      out << ".string \"" << name << "\"" << std::endl;
      out << ".byte 0" << std::endl;
      nameOffset += name.size() + 1;
   }
   out << std::endl;
}

int main(int argc, char **argv)
{
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
         writeExports(out, false, funcExports);
      }

      if (dataExports.size() > 0) {
         writeExports(out, true, dataExports);
      }
   }

   return 0;
}
