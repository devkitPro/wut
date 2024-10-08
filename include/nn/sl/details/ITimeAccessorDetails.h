#pragma once

#include <wut.h>
#include <coreinit/time.h>
#include <nn/result.h>

#ifdef __cplusplus

namespace nn::sl
{
class Condition;
class DrcManager;
class KillerNotificationSelector;
class TitleListCache;

namespace details
{
class ITimeAccessorBase;
struct ITimeAccessorInternal;

typedef nn::Result (*ITimeAccessor_GetNetworkTimeFn)(ITimeAccessorInternal *, OSTime *, bool *);
typedef nn::Result (*ITimeAccessor_GetLocalTimeFn)(ITimeAccessorInternal *, OSTime *, bool *);

struct WUT_PACKED ITimeAccessorInternalVTable
{
   ITimeAccessorBase *instance; // Is normally padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   ITimeAccessor_GetNetworkTimeFn GetNetworkTimeFn;
   WUT_PADDING_BYTES(4);
   ITimeAccessor_GetLocalTimeFn GetLocalTimeFn;
};
WUT_CHECK_SIZE(ITimeAccessorInternalVTable, 0x20);
WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x14, GetNetworkTimeFn);
WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x1C, GetLocalTimeFn);

typedef struct WUT_PACKED ITimeAccessorInternal
{
   ITimeAccessorInternalVTable *vtable;
} ITimeAccessorInternal;
WUT_CHECK_SIZE(ITimeAccessorInternal, 0x04);
WUT_CHECK_OFFSET(ITimeAccessorInternal, 0x00, vtable);

class ITimeAccessorBase
{
   friend class nn::sl::Condition;
   friend class nn::sl::DrcManager;
   friend class nn::sl::KillerNotificationSelector;
   friend class nn::sl::TitleListCache;

public:
   ITimeAccessorBase()          = default;

   virtual ~ITimeAccessorBase() = default;

   virtual nn::Result
   GetNetworkTime(OSTime *, bool *) const = 0;
   virtual nn::Result
   GetLocalTime(OSTime *, bool *) const = 0;

private:
   virtual details::ITimeAccessorInternal *
   GetInternal() = 0;
};

class TimeAccessorFromPtr : public ITimeAccessorBase
{
public:
   explicit TimeAccessorFromPtr(details::ITimeAccessorInternal *ptr) :
      mInstancePtr(ptr)
   {
   }
   nn::Result
   GetNetworkTime(OSTime *outTime, bool *outSuccess) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetNetworkTimeFn(mInstancePtr, outTime, outSuccess);
   }
   nn::Result
   GetLocalTime(OSTime *outTime, bool *outSuccess) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetLocalTimeFn(mInstancePtr, outTime, outSuccess);
   }

private:
   details::ITimeAccessorInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::ITimeAccessorInternal *mInstancePtr;
};
} // namespace details


} // namespace nn::sl

#endif