#pragma once

#ifdef __cplusplus

#include <cstdio>
#include <nn/idb/idb_cpp.h>
#include <nn/result.h>
#include <string>

namespace nn::idb
{
class IDBReader
{
public:
   IDBReader() = default;

   ~IDBReader();

   nn::Result
   LoadIconDataFromIdb(uint64_t titleId, nn::idb::IconDataRaw &iconData) const;

   bool
   SearchFromDataBase(nn::idb::IconDataKey &key, uint32_t &outIndex) const;

   bool
   LoadIconDataFromDatabase(uint32_t index, nn::idb::IconDataRaw &iconData) const;

   bool
   LoadIconData(uint64_t titleId, uint32_t u1, nn::idb::IconDataRaw &iconData) const;

   /**
    * Initializes the IDBReader from a custom path
    * @param path Path to "BaristaIconDataBase.dat"
    * @return true on success, false on error
    */
   bool
   Initialize(const std::string &path);

   /**
     * Initializes the IDBReader to read icons from the Wii U Menu icon cache
     * (fs:/vol/storage_mlc01/usr/save/%08X/%08X/user/common/BaristaIconDataBase.dat)
     * @return true on success, false on error
     */
   bool
   Initialize();

   void
   Finalize();

private:
   bool
   InitializeFile();

   void
   FinalizeFile();

   int
   LoadFromFile(void *buffer, uint32_t size, uint32_t offset) const;

   std::string mPath       = {};
   FileHeader *mFileHeader = {};
   FILE *mFile             = {};
   bool mInitDone          = false;
};
} // namespace nn::idb

#endif