#pragma once
#include "readrpl.h"

bool
verifyFile(const Rpl &rpl);

bool
verifyCrcs(const Rpl &rpl);

bool
verifyFileBounds(const Rpl &rpl);

bool
verifyRelocationTypes(const Rpl &rpl);

bool
verifySectionAlignment(const Rpl &rpl);

bool
verifySectionOrder(const Rpl &rpl);
