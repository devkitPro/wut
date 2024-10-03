#pragma once

#ifdef __cplusplus

#include <wut.h>
#include <cstdint>

namespace nn::idb
{
struct WUT_PACKED FileHeaderEntry
{
   uint64_t titleId;
   uint32_t u1;
   WUT_UNKNOWN_BYTES(0xC);
};
WUT_CHECK_SIZE(FileHeaderEntry, 0x18);
WUT_CHECK_OFFSET(FileHeaderEntry, 0x00, titleId);
WUT_CHECK_OFFSET(FileHeaderEntry, 0x08, u1);

struct WUT_PACKED FileHeader
{
   uint32_t version;
   FileHeaderEntry entries[300];
};
WUT_CHECK_SIZE(FileHeader, 0x1c24);
WUT_CHECK_OFFSET(FileHeader, 0x00, version);
WUT_CHECK_OFFSET(FileHeader, 0x04, entries);

struct WUT_PACKED IconDataKey
{
   uint64_t titleId;
   uint32_t u1; // maybe some kind of filter (or version)?
};
WUT_CHECK_SIZE(IconDataKey, 0xC);
WUT_CHECK_OFFSET(IconDataKey, 0x00, titleId);
WUT_CHECK_OFFSET(IconDataKey, 0x08, u1);

struct WUT_PACKED Utf16NameBuffer
{
   char16_t utf16Str[0x100];
};
WUT_CHECK_SIZE(Utf16NameBuffer, 0x200);
WUT_CHECK_OFFSET(Utf16NameBuffer, 0x00, utf16Str);

struct WUT_PACKED IconDataRaw
{
   uint64_t titleID;
   WUT_UNKNOWN_BYTES(0xC);
   char u6[0x10];
   WUT_UNKNOWN_BYTES(0xC);
   Utf16NameBuffer names[0xF];
   WUT_UNKNOWN_BYTES(0x200);
   uint8_t icon[0x1002c];
   WUT_UNKNOWN_BYTES(0x4);
};
WUT_CHECK_SIZE(IconDataRaw, 0x12060);
WUT_CHECK_OFFSET(IconDataRaw, 0x00, titleID);
WUT_CHECK_OFFSET(IconDataRaw, 0x30, names);
WUT_CHECK_OFFSET(IconDataRaw, 0x2030, icon);
} // namespace nn::idb

#endif