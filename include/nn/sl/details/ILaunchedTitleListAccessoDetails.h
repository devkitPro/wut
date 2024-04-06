#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class KillerNotificationSelector;
    namespace details {
        class ILaunchedTitleListAccessorBase;
        struct ILaunchedTitleListAccessorInternal;

        typedef nn::Result (*ILaunchedTitleListAccessor_GetByAccountFn)(ILaunchedTitleListAccessorInternal *, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId);

        struct WUT_PACKED ILaunchedTitleListAccessorInternalVTable {
            ILaunchedTitleListAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ILaunchedTitleListAccessor_GetByAccountFn GetByAccountFn;
        };
        WUT_CHECK_SIZE(ILaunchedTitleListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(ILaunchedTitleListAccessorInternalVTable, 0x14, GetByAccountFn);

        typedef struct WUT_PACKED ILaunchedTitleListAccessorInternal {
            ILaunchedTitleListAccessorInternalVTable *vtable;
        } ILaunchedTitleListAccessorInternal;
        WUT_CHECK_SIZE(ILaunchedTitleListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(ILaunchedTitleListAccessorInternal, 0x00, vtable);

        class ILaunchedTitleListAccessorBase {
            friend class nn::sl::KillerNotificationSelector;

        public:
            ILaunchedTitleListAccessorBase()          = default;
            virtual ~ILaunchedTitleListAccessorBase() = default;

            virtual nn::Result GetByAccount(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) = 0;

        private:
            virtual details::ILaunchedTitleListAccessorInternal *GetInternal() = 0;
        };

        class LaunchedTitleListAccessorFromPtr : public ILaunchedTitleListAccessorBase {
        public:
            explicit LaunchedTitleListAccessorFromPtr(details::ILaunchedTitleListAccessorInternal *ptr) : mInstancePtr(ptr) {
            }

            nn::Result GetByAccount(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) override;

            details::ILaunchedTitleListAccessorInternal *GetInternal() override;

        private:
            details::ILaunchedTitleListAccessorInternal *mInstancePtr;
        };


    } // namespace details

} // namespace nn::sl

#endif