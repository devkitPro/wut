#pragma once
#include "readrpl.h"

std::string
formatSHT(uint32_t type);

void
printHeader(const Rpl &rpl);

void
printSectionSummary(const Rpl &rpl);

void
printFileInfo(const Rpl &rpl,
              const Section &section);

void
printRela(const Rpl &rpl,
          const Section &section);

void
printSymTab(const Rpl &rpl,
            const Section &section);

void
printRplImports(const Rpl &rpl,
                const Section &section);

void
printRplCrcs(const Rpl &rpl,
             const Section &section);

void
printRplExports(const Rpl &rpl,
                const Section &section);
