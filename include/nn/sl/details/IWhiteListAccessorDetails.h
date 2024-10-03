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
class IWhiteListAccessorBase;
struct IWhiteListAccessorInternal;

typedef nn::Result (*IWhiteListAccessor_GetFn)(IWhiteListAccessorInternal *, nn::sl::WhiteList *);

struct WUT_PACKED IWhiteListAccessorInternalVTable
{
   IWhiteListAccessorBase *instance; // normally this is padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   IWhiteListAccessor_GetFn GetFn;
};
WUT_CHECK_SIZE(IWhiteListAccessorInternalVTable, 0x18);
WUT_CHECK_OFFSET(IWhiteListAccessorInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(IWhiteListAccessorInternalVTable, 0x14, GetFn);

typedef struct WUT_PACKED IWhiteListAccessorInternal
{
   IWhiteListAccessorInternalVTable *vtable;
} IWhiteListAccessorInternal;
WUT_CHECK_SIZE(IWhiteListAccessorInternal, 0x04);
WUT_CHECK_OFFSET(IWhiteListAccessorInternal, 0x00, vtable);

class IWhiteListAccessorBase
{
   friend class nn::sl::QuickStartApplicationSelector;

public:
   IWhiteListAccessorBase()          = default;
   virtual ~IWhiteListAccessorBase() = default;

   virtual nn::Result
   Get(nn::sl::WhiteList *outWhiteList) const = 0;

private:
   virtual details::IWhiteListAccessorInternal *
   GetInternal() = 0;
};

class WhiteListAccessorFromPtr : public IWhiteListAccessorBase
{
public:
   explicit WhiteListAccessorFromPtr(details::IWhiteListAccessorInternal *ptr) :
      mInstancePtr(ptr)
   {
   }
   nn::Result
   Get(nn::sl::WhiteList *outWhiteList) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetFn(mInstancePtr, outWhiteList);
   }

private:
   nn::sl::details::IWhiteListAccessorInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::IWhiteListAccessorInternal *mInstancePtr;
};
} // namespace details

} // namespace nn::sl

#endif