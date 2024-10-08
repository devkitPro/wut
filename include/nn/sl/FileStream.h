#pragma once

#include <wut.h>
#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <nn/sl/IStream.h>
#include <nn/sl/details/IStreamDetails.h>

#ifdef __cplusplus

namespace nn::sl
{
namespace details
{
typedef struct WUT_PACKED FileStreamInternal
{
   void *vtable;
   FSClient *fsClient;
   FSCmdBlock *fsCmdBlock;
   FSFileHandle fileHandle;
} FileStreamInternal;
WUT_CHECK_SIZE(FileStreamInternal, 0x10);
WUT_CHECK_OFFSET(FileStreamInternal, 0x00, vtable);
WUT_CHECK_OFFSET(FileStreamInternal, 0x04, fsClient);
WUT_CHECK_OFFSET(FileStreamInternal, 0x08, fsCmdBlock);
WUT_CHECK_OFFSET(FileStreamInternal, 0x0C, fileHandle);

extern "C" nn::Result
Initialize__Q3_2nn2sl10FileStreamFP8FSClientP10FSCmdBlockPCcT3(FileStreamInternal *, FSClient *, FSCmdBlock *, char const *, char const *);
extern "C" FileStreamInternal *
__ct__Q3_2nn2sl10FileStreamFv(FileStreamInternal *);
extern "C" void
__dt__Q3_2nn2sl10FileStreamFv(FileStreamInternal *, int);
} // namespace details

class FileStream : public details::IStreamBase
{
public:
   FileStream()
   {
      __ct__Q3_2nn2sl10FileStreamFv(&mInstance);
   }

   ~FileStream() override
   {
      __dt__Q3_2nn2sl10FileStreamFv(&mInstance, 2);
   }

   nn::Result
   Read(uint32_t *bytesRead, void *buffer, uint32_t readSize) override
   {
      auto *base = reinterpret_cast<details::IStreamInternal *>(&mInstance);
      return base->vtable->ReadFn(base, bytesRead, buffer, readSize);
   }
   nn::Result
   Write(uint32_t *bytesWritten, void *buffer, uint32_t readSize) override
   {
      auto *base = reinterpret_cast<details::IStreamInternal *>(&mInstance);
      return base->vtable->WriteFn(base, bytesWritten, buffer, readSize);
   }
   nn::Result
   GetSize(uint32_t *fileSize) override
   {
      auto *base = reinterpret_cast<details::IStreamInternal *>(&mInstance);
      return base->vtable->GetSizeFn(base, fileSize);
   }
   nn::Result
   Seek(int32_t offset, nn::sl::SeekOrigin seekOrigin) override
   {
      auto *base = reinterpret_cast<details::IStreamInternal *>(&mInstance);
      return base->vtable->SeekFn(base, offset, seekOrigin);
   }

   /**
         * The given client and cmd must be valid during the whole liftime of the filestream
         */
   nn::Result
   Initialize(FSClient *client, FSCmdBlock *cmdBlock, char const *path, char const *mode)
   {
      return Initialize__Q3_2nn2sl10FileStreamFP8FSClientP10FSCmdBlockPCcT3(&mInstance, client, cmdBlock, path, mode);
   }

   details::IStreamInternal *
   GetInternal() override
   {
      return reinterpret_cast<details::IStreamInternal *>(&mInstance);
   }

private:
   details::FileStreamInternal mInstance = {};
};

}; // namespace nn::sl

#endif