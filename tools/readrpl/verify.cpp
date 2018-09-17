#include "verify.h"
#include <algorithm>
#include <fmt/format.h>
#include <set>
#include <zlib.h>

static bool
sValidateRelocsAddTable(const Rpl &rpl,
                        const Section &section)
{
   const auto &header = section.header;
   if (!header.size) {
      return true;
   }

   auto entsize = static_cast<uint32_t>(header.entsize);
   if (!entsize) {
      entsize = static_cast<uint32_t>(sizeof(elf::Rela));
   }

   if (entsize < sizeof(elf::Rela)) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0002E);
      return false;
   }

   auto numRelas = (header.size / entsize);
   if (!numRelas) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0000A);
      return false;
   }

   if (!header.link || header.link >= rpl.header.shnum) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0000B);
      return false;
   }

   const auto &symbolSection = rpl.sections[header.link];
   if (symbolSection.header.type != elf::SHT_SYMTAB) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0000C);
      return false;
   }

   auto symEntsize = symbolSection.header.entsize ?
                     static_cast<uint32_t>(symbolSection.header.entsize) :
                     static_cast<uint32_t>(sizeof(elf::Symbol));
   if (symEntsize < sizeof(elf::Symbol)) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0002F);
      return false;
   }

   if (header.info >= rpl.header.shnum) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0000D);
      return false;
   }

   const auto &targetSection = rpl.sections[header.info];
   if (targetSection.header.type != elf::SHT_NULL) {
      auto numSymbols = symbolSection.data.size() / symEntsize;
      for (auto i = 0u; i < numRelas; ++i) {
         auto rela = reinterpret_cast<const elf::Rela *>(section.data.data() + i * entsize);
         if (rela->info && (rela->info >> 8) >= numSymbols) {
            fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0000F);
            return false;
         }
      }
   }

   return true;
}

static bool
sValidateSymbolTable(const Rpl &rpl,
                     const Section &section)
{
   auto result = true;
   const auto &header = section.header;
   if (!header.size) {
      return true;
   }

   const Section *symStrTabSection = nullptr;
   if (header.link) {
      if (header.link >= rpl.header.shnum) {
         fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00001);
         return false;
      }

      symStrTabSection = &rpl.sections[header.link];
      if (symStrTabSection->header.type != elf::SHT_STRTAB) {
         fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00002);
         return false;
      }
   }

   auto entsize = header.entsize ?
                  static_cast<uint32_t>(header.entsize) :
                  static_cast<uint32_t>(sizeof(elf::Symbol));
   if (entsize < sizeof(elf::Symbol)) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0002D);
      return false;
   }

   auto numSymbols = header.size / entsize;
   if (!numSymbols) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00003);
      result = false;
   }

   for (auto i = 0u; i < numSymbols; ++i) {
      auto symbol = reinterpret_cast<const elf::Symbol *>(section.data.data() + i * entsize);

      if (symStrTabSection &&
          symbol->name > symStrTabSection->data.size()) {
         fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00004);
      }

      auto type = symbol->info & 0xF;
      if (symbol->shndx &&
          symbol->shndx < elf::SHN_LORESERVE &&
          type != elf::STT_SECTION &&
          type != elf::STT_FILE) {
         if (symbol->shndx >= rpl.header.shnum) {
            fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00005);
            result = false;
         } else if (type == elf::STT_OBJECT) {
            const auto &targetSection = rpl.sections[symbol->shndx];
            auto targetSectionSize = targetSection.data.size() ?
                                     static_cast<uint32_t>(targetSection.data.size()) :
                                     static_cast<uint32_t>(targetSection.header.size);

            if (targetSectionSize &&
                targetSection.header.flags & elf::SHF_ALLOC) {
               if (targetSection.header.type == elf::SHT_NULL) {
                  fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00006);
                  result = false;
               }

               auto position = symbol->value - targetSection.header.addr;
               if (position > targetSectionSize || position + symbol->size > targetSectionSize) {
                  fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00007);
                  result = false;
               }
            }
         } else if (type == elf::STT_FUNC) {
            const auto &targetSection = rpl.sections[symbol->shndx];
            auto targetSectionSize = targetSection.data.size() ?
                                     static_cast<uint32_t>(targetSection.data.size()) :
                                     static_cast<uint32_t>(targetSection.header.size);

            if (targetSectionSize &&
                targetSection.header.flags & elf::SHF_ALLOC) {
               if (targetSection.header.type == elf::SHT_NULL) {
                  fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00008);
                  result = false;
               }

               auto position = symbol->value - targetSection.header.addr;
               if (position > targetSectionSize || position + symbol->size > targetSectionSize) {
                  fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00009);
                  result = false;
               }
            }
         }
      }
   }

   return result;
}

/**
 * Equivalent to loader.elf ELFFILE_ValidateAndPrepare
 */
bool
verifyFile(const Rpl &rpl)
{
   const auto &header = rpl.header;
   auto result = true;

   if (rpl.fileSize < 0x104) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00018);
      return false;
   }

   if (header.magic != elf::HeaderMagic) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00019);
      result = false;
   }

   if (header.fileClass != elf::ELFCLASS32) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001A);
      result = false;
   }

   if (header.elfVersion > elf::EV_CURRENT) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001B);
      result = false;
   }

   if (!header.machine) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001C);
      result = false;
   }

   if (!header.version != 1) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001D);
      result = false;
   }

   auto ehsize = static_cast<uint32_t>(header.ehsize);
   if (ehsize) {
      if (header.ehsize < sizeof(elf::Header)) {
         fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001E);
         result = false;
      }
   } else {
      ehsize = static_cast<uint32_t>(sizeof(elf::Header));
   }

   auto phoff = header.phoff;
   if (phoff && (phoff < ehsize || phoff >= rpl.fileSize)) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0001F);
      result = false;
   }

   auto shoff = header.shoff;
   if (shoff && (shoff < ehsize || shoff >= rpl.fileSize)) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00020);
      result = false;
   }

   if (header.shstrndx && header.shstrndx >= header.shnum) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00021);
      result = false;
   }

   auto phentsize = header.phentsize ?
                    static_cast<uint16_t>(header.phentsize) :
                    static_cast<uint16_t>(32);
   if (header.phoff &&
       (header.phoff + phentsize * header.phnum) > rpl.fileSize) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00022);
      result = false;
   }

   auto shentsize = header.shentsize ?
                    static_cast<uint32_t>(header.shentsize) :
                    static_cast<uint32_t>(sizeof(elf::SectionHeader));
   if (header.shoff &&
      (header.shoff + shentsize * header.shnum) > rpl.fileSize) {
      fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00023);
      result = false;
   }

   for (auto &section : rpl.sections) {
      if (section.header.size &&
          section.header.type != elf::SHT_NOBITS) {
         if (section.header.offset < ehsize) {
            fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00024);
            result = false;
         }

         if (section.header.offset >= shoff &&
             section.header.offset < (shoff + header.shnum * shentsize)) {
            fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD00027);
            result = false;
         }
      }
   }

   if (header.shstrndx) {
      const auto &shStrTabSection = rpl.sections[header.shstrndx];
      if (shStrTabSection.header.type != elf::SHT_STRTAB) {
         fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0002A);
         result = false;
      } else {
         for (auto &section : rpl.sections) {
            if (section.header.name >= shStrTabSection.data.size()) {
               fmt::format("*** Failed ELF file checks (err=0x{:08X})\n", 0xBAD0002B);
               result = false;
            }
         }
      }
   }

   for (const auto &section : rpl.sections) {
      if (section.header.type == elf::SHT_RELA) {
         result = sValidateRelocsAddTable(rpl, section) && result;
      } else if (section.header.type == elf::SHT_SYMTAB) {
         result = sValidateSymbolTable(rpl, section) && result;
      }
   }

   return result;
}


/**
 * Verify values in SHT_RPL_CRCS
 */
bool
verifyCrcs(const Rpl &rpl)
{
   const elf::RplCrc *crcs = NULL;
   auto result = true;

   for (const auto &section : rpl.sections) {
      if (section.header.type == elf::SHT_RPL_CRCS) {
         crcs = reinterpret_cast<const elf::RplCrc *>(section.data.data());
         break;
      }
   }

   if (!crcs) {
      return false;
   }

   auto sectionIndex = 0u;
   for (const auto &section : rpl.sections) {
      auto crc = uint32_t { 0u };
      if (section.header.type != elf::SHT_RPL_CRCS &&
          section.data.size()) {
         crc = crc32(0, Z_NULL, 0);
         crc = crc32(crc, reinterpret_cast<const Bytef *>(section.data.data()), section.data.size());
      }

      if (crc != crcs[sectionIndex].crc) {
         fmt::print("Unexpected crc for section {}, read 0x{:08X} but calculated 0x{:08X}",
                    sectionIndex, crcs[sectionIndex].crc, crc);
         result = false;
      }

      sectionIndex++;
   }

   return result;
}


/**
 * Equivalent to loader.elf LiCheckFileBounds
 */
bool
verifyFileBounds(const Rpl &rpl)
{
   auto result = true;
   auto dataMin = 0xFFFFFFFFu;
   auto dataMax = 0u;

   auto readMin = 0xFFFFFFFFu;
   auto readMax = 0u;

   auto textMin = 0xFFFFFFFFu;
   auto textMax = 0u;

   auto tempMin = 0xFFFFFFFFu;
   auto tempMax = 0u;

   for (const auto &section : rpl.sections) {
      if (section.header.size == 0 ||
          section.header.type == elf::SHT_RPL_FILEINFO ||
          section.header.type == elf::SHT_RPL_CRCS ||
          section.header.type == elf::SHT_NOBITS ||
          section.header.type == elf::SHT_RPL_IMPORTS) {
         continue;
      }

      if ((section.header.flags & elf::SHF_EXECINSTR) &&
           section.header.type != elf::SHT_RPL_EXPORTS) {
         textMin = std::min<uint32_t>(textMin, section.header.offset);
         textMax = std::max<uint32_t>(textMax, section.header.offset + section.header.size);
      } else {
         if (section.header.flags & elf::SHF_ALLOC) {
            if (section.header.flags & elf::SHF_WRITE) {
               dataMin = std::min<uint32_t>(dataMin, section.header.offset);
               dataMax = std::max<uint32_t>(dataMax, section.header.offset + section.header.size);
            } else {
               readMin = std::min<uint32_t>(readMin, section.header.offset);
               readMax = std::max<uint32_t>(readMax, section.header.offset + section.header.size);
            }
         } else {
            tempMin = std::min<uint32_t>(tempMin, section.header.offset);
            tempMax = std::max<uint32_t>(tempMax, section.header.offset + section.header.size);
         }
      }
   }

   if (dataMin == 0xFFFFFFFFu) {
      dataMin = (rpl.header.shnum * rpl.header.shentsize) + rpl.header.shoff;
      dataMax = dataMin;
   }

   if (readMin == 0xFFFFFFFFu) {
      readMin = dataMax;
      readMax = dataMax;
   }

   if (textMin == 0xFFFFFFFFu) {
      textMin = readMax;
      textMax = readMax;
   }

   if (tempMin == 0xFFFFFFFFu) {
      tempMin = textMax;
      tempMax = textMax;
   }

   if (dataMin < rpl.header.shoff) {
      fmt::print("*** SecHrs, FileInfo, or CRCs in bad spot in file. Return %d.\n", -470026);
      result = false;
   }

   // Data
   if (dataMin > dataMax) {
      fmt::print("*** DataMin > DataMax. break.\n");
      result = false;
   }

   if (dataMin > readMin) {
      fmt::print("*** DataMin > ReadMin. break.\n");
      result = false;
   }

   if (dataMax > readMin) {
      fmt::print("*** DataMax > ReadMin, break.\n");
      result = false;
   }

   // Read
   if (readMin > readMax) {
      fmt::print("*** ReadMin > ReadMax. break.\n");
      result = false;
   }

   if (readMin > textMin) {
      fmt::print("*** ReadMin > TextMin. break.\n");
      result = false;
   }

   if (readMax > textMin) {
      fmt::print("*** ReadMax > TextMin. break.\n");
      result = false;
   }

   // Text
   if (textMin > textMax) {
      fmt::print("*** TextMin > TextMax. break.\n");
      result = false;
   }

   if (textMin > tempMin) {
      fmt::print("*** TextMin > TempMin. break.\n");
      result = false;
   }

   if (textMax > tempMin) {
      fmt::print("*** TextMax > TempMin. break.\n");
      result = false;
   }

   // Temp
   if (tempMin > tempMax) {
      fmt::print("*** TempMin > TempMax. break.\n");
      result = false;
   }

   if (!result) {
      fmt::print("dataMin = 0x{:08X}\n", dataMin);
      fmt::print("dataMax = 0x{:08X}\n", dataMax);
      fmt::print("readMin = 0x{:08X}\n", readMin);
      fmt::print("readMax = 0x{:08X}\n", readMax);
      fmt::print("textMin = 0x{:08X}\n", textMin);
      fmt::print("textMax = 0x{:08X}\n", textMax);
      fmt::print("tempMin = 0x{:08X}\n", tempMin);
      fmt::print("tempMax = 0x{:08X}\n", tempMax);
   }

   return result;
}


/**
 * Check that the rpl only uses relocation types which are supported by
 * loader.elf
 */
bool
verifyRelocationTypes(const Rpl &rpl)
{
   std::set<unsigned int> unsupportedTypes;

   for (auto &section : rpl.sections) {
      if (section.header.type != elf::SHT_RELA) {
         continue;
      }

      auto &symbolSection = rpl.sections[section.header.link];
      auto &targetSection = rpl.sections[section.header.info];
      auto rels = reinterpret_cast<const elf::Rela *>(section.data.data());
      auto numRels = section.data.size() / sizeof(elf::Rela);

      for (auto i = 0u; i < numRels; ++i) {
         auto info = rels[i].info;
         auto addend = rels[i].addend;
         auto offset = rels[i].offset;
         auto index = info >> 8;
         auto type = info & 0xFF;

         switch (type) {
         case elf::R_PPC_NONE:
         case elf::R_PPC_ADDR32:
         case elf::R_PPC_ADDR16_LO:
         case elf::R_PPC_ADDR16_HI:
         case elf::R_PPC_ADDR16_HA:
         case elf::R_PPC_REL24:
         case elf::R_PPC_REL14:
         case elf::R_PPC_DTPMOD32:
         case elf::R_PPC_DTPREL32:
         case elf::R_PPC_EMB_SDA21:
         case elf::R_PPC_EMB_RELSDA:
         case elf::R_PPC_DIAB_SDA21_LO:
         case elf::R_PPC_DIAB_SDA21_HI:
         case elf::R_PPC_DIAB_SDA21_HA:
         case elf::R_PPC_DIAB_RELSDA_LO:
         case elf::R_PPC_DIAB_RELSDA_HI:
         case elf::R_PPC_DIAB_RELSDA_HA:
         case elf::R_PPC_GHS_REL16_HA:
         case elf::R_PPC_GHS_REL16_HI:
         case elf::R_PPC_GHS_REL16_LO:
            // All valid relocations on Wii U, do nothing
            break;
         default:
            // Only print error once per type
            if (!unsupportedTypes.count(type)) {
               fmt::print("Unsupported relocation type {}\n", type);
               unsupportedTypes.insert(type);
            }
         }
      }
   }

   return unsupportedTypes.empty();
}


/**
 * Verify that section.addr is aligned by section.addralign
 */
bool
verifySectionAlignment(const Rpl &rpl)
{
   auto result = true;
   for (auto &section : rpl.sections) {
      if (!align_check(section.header.addr, section.header.addralign)) {
         fmt::print("Unaligned section {}, addr {}, addralign {}",
                    getSectionIndex(rpl, section),
                    section.header.addr,
                    section.header.addralign);
         result = false;
      }
   }
   return result;
}


bool
verifySectionOrder(const Rpl &rpl)
{
   auto lastSection = rpl.sections[rpl.header.shnum - 1];
   auto penultimateSection = rpl.sections[rpl.header.shnum - 2];


   if (lastSection.header.type != elf::SHT_RPL_FILEINFO ||
      (lastSection.header.flags & elf::SHF_DEFLATED)) {
      fmt::print("***shnum-1 section type = 0x{:08X}, flags=0x{:08X}\n",
                 lastSection.header.type,
                 lastSection.header.flags);
   }

   if (penultimateSection.header.type != elf::SHT_RPL_CRCS ||
      (penultimateSection.header.flags & elf::SHF_DEFLATED)) {
      fmt::print("***shnum-2 section type = 0x{:08X}, flags=0x{:08X}\n",
                 penultimateSection.header.type,
                 penultimateSection.header.flags);
   }

   return true;
}
