#pragma once
#include "readrpl.h"
#include <string>

bool
generateExportsDef(const Rpl &rpl,
                   const std::string &rplName,
                   const std::string &outFileName);
