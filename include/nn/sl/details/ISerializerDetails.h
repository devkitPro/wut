#pragma once

#include <wut.h>
#include <nn/result.h>

#ifdef __cplusplus

namespace nn::sl
{
template<typename T>
class ISerializerBase;

class TitleIconCache;
class DataCreator;
class CacheManager;
class Condition;
class KillerNotificationSelector;
class TitleListCache;

namespace details
{
struct ISerializerInternal;

typedef nn::Result (*ISerializer_SerializeFn)(ISerializerInternal *, void *, uint32_t);
typedef nn::Result (*ISerializer_DeserializeFn)(ISerializerInternal *, void *, uint32_t);
typedef nn::Result (*ISerializer_GetCountFn)(ISerializerInternal *, uint32_t *);

struct WUT_PACKED ISerializerInternalVTable
{
   ISerializerBase<uint8_t> *instance; // Is normally padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   ISerializer_SerializeFn SerializeFn;
   WUT_PADDING_BYTES(4);
   ISerializer_DeserializeFn DeserializeFn;
   WUT_PADDING_BYTES(4);
   ISerializer_GetCountFn GetCountFn;
};
WUT_CHECK_SIZE(ISerializerInternalVTable, 0x28);
WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x14, SerializeFn);
WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x1C, DeserializeFn);
WUT_CHECK_OFFSET(ISerializerInternalVTable, 0x24, GetCountFn);

typedef struct WUT_PACKED ISerializerInternal
{
   ISerializerInternalVTable *vtable;
} ISerializerInternal;
WUT_CHECK_SIZE(ISerializerInternal, 0x04);
WUT_CHECK_OFFSET(ISerializerInternal, 0x00, vtable);

template<typename T>
class ISerializerBase
{
   friend class nn::sl::TitleIconCache;
   friend class nn::sl::DataCreator;
   friend class nn::sl::CacheManager;
   friend class nn::sl::Condition;
   friend class nn::sl::KillerNotificationSelector;
   friend class nn::sl::TitleListCache;

public:
   ISerializerBase()          = default;

   virtual ~ISerializerBase() = default;

   virtual nn::Result
   Serialize(void *buffer, uint32_t size) const = 0;

   virtual nn::Result
   Deserialize(void *buffer, uint32_t size) const = 0;

   virtual nn::Result
   GetCount(uint32_t *outCount) const = 0;

private:
   virtual details::ISerializerInternal *
   GetInternal() = 0;
};


template<typename T>
class SerializerFromPtr : public ISerializerBase<T>
{
public:
   explicit SerializerFromPtr(details::ISerializerInternal *ptr) :
      mInstancePtr(ptr)
   {
   }

   nn::Result
   Serialize(void *buffer, uint32_t size) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->SerializeFn(mInstancePtr, buffer, size);
   }

   nn::Result
   Deserialize(void *buffer, uint32_t size) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->DeserializeFn(mInstancePtr, buffer, size);
   }

   nn::Result
   GetCount(uint32_t *outCount) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetCountFn(mInstancePtr, outCount);
   }

private:
   details::ISerializerInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::ISerializerInternal *mInstancePtr;
};
} // namespace details

} // namespace nn::sl

#endif