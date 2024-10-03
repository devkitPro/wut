#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class QuickStartApplicationSelector;
namespace details
{
class IDefaultTitleAccessorBase;
struct IDefaultTitleAccessorInternal;

typedef nn::Result (*IDefaultTitleAccessor_GetFn)(IDefaultTitleAccessorInternal *, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

struct WUT_PACKED IDefaultTitleAccessorInternalVTable
{
   IDefaultTitleAccessorBase *instance; // normally this is padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   IDefaultTitleAccessor_GetFn GetFn;
};
WUT_CHECK_SIZE(IDefaultTitleAccessorInternalVTable, 0x18);
WUT_CHECK_OFFSET(IDefaultTitleAccessorInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(IDefaultTitleAccessorInternalVTable, 0x14, GetFn);

typedef struct WUT_PACKED IDefaultTitleAccessorInternal
{
   IDefaultTitleAccessorInternalVTable *vtable;
} IDefaultTitleAccessorInternal;
WUT_CHECK_SIZE(IDefaultTitleAccessorInternal, 0x04);
WUT_CHECK_OFFSET(IDefaultTitleAccessorInternal, 0x00, vtable);

class IDefaultTitleAccessorBase
{
   friend class nn::sl::QuickStartApplicationSelector;

public:
   IDefaultTitleAccessorBase()          = default;
   virtual ~IDefaultTitleAccessorBase() = default;

   virtual nn::Result
   Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) = 0;

private:
   virtual details::IDefaultTitleAccessorInternal *
   GetInternal() = 0;
};

class DefaultTitleAccessorFromPtr : public IDefaultTitleAccessorBase
{
public:
   explicit DefaultTitleAccessorFromPtr(details::IDefaultTitleAccessorInternal *ptr) :
      mInstancePtr(ptr)
   {
   }
   nn::Result
   Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
   }

private:
   nn::sl::details::IDefaultTitleAccessorInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::IDefaultTitleAccessorInternal *mInstancePtr;
};
} // namespace details

} // namespace nn::sl

#endif