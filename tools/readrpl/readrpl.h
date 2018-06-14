#pragma once
#include "elf.h"
#include <string>
#include <vector>

struct Section
{
   elf::SectionHeader header;
   std::string name;
   std::vector<char> data;
};

struct Rpl
{
   elf::Header header;
   uint32_t fileSize;
   std::vector<Section> sections;
};

uint32_t
getSectionIndex(const Rpl &rpl,
                const Section &section);
