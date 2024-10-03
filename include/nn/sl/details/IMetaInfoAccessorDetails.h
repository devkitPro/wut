#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class TitleListCache;
namespace details
{
class IMetaInfoAccessorBase;
struct IMetaInfoAccessorInternal;

typedef nn::Result (*IMetaInfoAccessor_GetFn)(IMetaInfoAccessorInternal *, nn::sl::TitleMetaInfo *, const nn::sl::TitleInfo &);

struct WUT_PACKED IMetaInfoAccessorInternalVTable
{
   IMetaInfoAccessorBase *instance; // normally this is padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   IMetaInfoAccessor_GetFn GetFn;
};
WUT_CHECK_SIZE(IMetaInfoAccessorInternalVTable, 0x18);
WUT_CHECK_OFFSET(IMetaInfoAccessorInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(IMetaInfoAccessorInternalVTable, 0x14, GetFn);

typedef struct WUT_PACKED IMetaInfoAccessorInternal
{
   IMetaInfoAccessorInternalVTable *vtable;
} IMetaInfoAccessorInternal;
WUT_CHECK_SIZE(IMetaInfoAccessorInternal, 0x04);
WUT_CHECK_OFFSET(IMetaInfoAccessorInternal, 0x00, vtable);

class IMetaInfoAccessorBase
{
   friend class nn::sl::TitleListCache;

public:
   IMetaInfoAccessorBase()          = default;
   virtual ~IMetaInfoAccessorBase() = default;

   virtual nn::Result
   Get(nn::sl::TitleMetaInfo *outMetaInfo, const nn::sl::TitleInfo &titleInfo) const = 0;

private:
   virtual details::IMetaInfoAccessorInternal *
   GetInternal() = 0;
};

class MetaInfoAccessorFromPtr : public IMetaInfoAccessorBase
{
public:
   explicit MetaInfoAccessorFromPtr(details::IMetaInfoAccessorInternal *ptr) :
      mInstancePtr(ptr)
   {
   }
   nn::Result
   Get(nn::sl::TitleMetaInfo *outMetaInfo, const nn::sl::TitleInfo &titleInfo) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetFn(mInstancePtr, outMetaInfo, titleInfo);
   }

private:
   nn::sl::details::IMetaInfoAccessorInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::IMetaInfoAccessorInternal *mInstancePtr;
};
} // namespace details

} // namespace nn::sl

#endif