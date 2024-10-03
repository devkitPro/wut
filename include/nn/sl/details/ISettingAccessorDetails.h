#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class TitleIconCache;
class DataCreator;
class Condition;
class DrcManager;
class KillerNotificationSelector;
class QuickStartApplicationSelector;
namespace details
{
class ISettingAccessorBase;
struct ISettingAccessorInternal;

typedef nn::Result (*ISettingAccessor_GetFn)(ISettingAccessorInternal *, Setting *);

struct WUT_PACKED ISettingAccessorInternalVTable
{
   ISettingAccessorBase *instance; // Is normally padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   ISettingAccessor_GetFn GetFn;
};
WUT_CHECK_SIZE(ISettingAccessorInternalVTable, 0x18);
WUT_CHECK_OFFSET(ISettingAccessorInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(ISettingAccessorInternalVTable, 0x14, GetFn);

typedef struct WUT_PACKED ISettingAccessorInternal
{
   ISettingAccessorInternalVTable *vtable;
} ISettingAccessorInternal;
WUT_CHECK_SIZE(ISettingAccessorInternal, 0x04);
WUT_CHECK_OFFSET(ISettingAccessorInternal, 0x00, vtable);

class ISettingAccessorBase
{
   friend class nn::sl::TitleIconCache;
   friend class nn::sl::DataCreator;
   friend class nn::sl::Condition;
   friend class nn::sl::DrcManager;
   friend class nn::sl::KillerNotificationSelector;
   friend class nn::sl::QuickStartApplicationSelector;

public:
   ISettingAccessorBase()          = default;

   virtual ~ISettingAccessorBase() = default;

   virtual nn::Result
   Get(nn::sl::Setting *) const = 0;

private:
   virtual details::ISettingAccessorInternal *
   GetInternal() = 0;
};


class SettingAccessorFromPtr : public ISettingAccessorBase
{
public:
   explicit SettingAccessorFromPtr(details::ISettingAccessorInternal *ptr) :
      mInstancePtr(ptr)
   {
   }

   nn::Result
   Get(nn::sl::Setting *outSetting) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->GetFn(mInstancePtr, outSetting);
   }

private:
   details::ISettingAccessorInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::ISettingAccessorInternal *mInstancePtr;
};
} // namespace details
} // namespace nn::sl

#endif