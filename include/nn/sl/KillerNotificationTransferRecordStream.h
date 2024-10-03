#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/FileStream.h>

#ifdef __cplusplus

namespace nn::sl
{
namespace details
{
typedef struct WUT_PACKED KillerNotificationTransferRecordStreamInternal
{
   void *vtable;
   FileStreamInternal fileStream;
   uint32_t unkn1;
   WUT_UNKNOWN_BYTES(0x84);
} KillerNotificationTransferRecordStreamInternal;
WUT_CHECK_SIZE(KillerNotificationTransferRecordStreamInternal, 0x9C);
WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x00, vtable);
WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x04, fileStream);
WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x14, unkn1);
} // namespace details

class KillerNotificationTransferRecordStream : public nn::sl::details::IStreamBase
{
public:
   explicit KillerNotificationTransferRecordStream(details::KillerNotificationTransferRecordStreamInternal *instance) :
      mInstance(instance)
   {
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

   ~KillerNotificationTransferRecordStream() override = default;

   details::IStreamInternal *
   GetInternal() override
   {
      return reinterpret_cast<details::IStreamInternal *>(mInstance);
   }

private:
   details::KillerNotificationTransferRecordStreamInternal *mInstance = {};
};

nn::sl::details::IStreamBase &
GetDefaultKillerNotificationTransferRecordStream();
} // namespace nn::sl

#endif