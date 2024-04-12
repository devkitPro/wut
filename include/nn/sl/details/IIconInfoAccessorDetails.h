#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class DataCreator;
    class TitleIconCache;
    namespace details {
        class IIconInfoAccessorBase;
        struct IIconInfoAccessorInternal;

        typedef nn::Result (*IconInfoAccessor_GetTitleIconInfoFn)(IIconInfoAccessorInternal *, nn::sl::IconInfo *, const nn::sl::TitleInfo &, nn::sl::Language);
        typedef nn::Result (*IconInfoAccessor_GetMiiIconFn)(IIconInfoAccessorInternal *, void *buffer, uint32_t buffer_size, uint32_t slot);

        struct WUT_PACKED IIconInfoAccessorInternalVTable {
            IIconInfoAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IconInfoAccessor_GetTitleIconInfoFn GetTitleIconInfoFn;
            WUT_PADDING_BYTES(4);
            IconInfoAccessor_GetMiiIconFn GetMiiIconFn;
            WUT_PADDING_BYTES(4);
        };
        WUT_CHECK_SIZE(IIconInfoAccessorInternalVTable, 0x24);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternalVTable, 0x14, GetTitleIconInfoFn);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternalVTable, 0x1C, GetMiiIconFn);

        typedef struct WUT_PACKED IIconInfoAccessorInternal {
            IIconInfoAccessorInternalVTable *vtable;
        } IIconInfoAccessorInternal;
        WUT_CHECK_SIZE(IIconInfoAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternal, 0x00, vtable);

        class IIconInfoAccessorBase {
            friend class nn::sl::DataCreator;
            friend class nn::sl::TitleIconCache;

        public:
            IIconInfoAccessorBase()          = default;
            virtual ~IIconInfoAccessorBase() = default;

            virtual nn::Result GetTitleIconInfo(nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) const = 0;

            virtual nn::Result GetMiiIcon(void *buffer, uint32_t buffer_size, uint32_t slot) const = 0;

        private:
            virtual details::IIconInfoAccessorInternal *GetInternal() = 0;
        };

        class IconInfoAccessorFromPtr : public IIconInfoAccessorBase {
        public:
            explicit IconInfoAccessorFromPtr(details::IIconInfoAccessorInternal *ptr) : mInstancePtr(ptr) {
            }

            nn::Result GetTitleIconInfo(nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) const override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetTitleIconInfoFn(mInstancePtr, outIconInfo, titleInfo, language);
            }

            nn::Result GetMiiIcon(void *buffer, uint32_t buffer_size, uint32_t slot) const override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetMiiIconFn(mInstancePtr, buffer, buffer_size, slot);
            }

        private:
            nn::sl::details::IIconInfoAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IIconInfoAccessorInternal *mInstancePtr;
        };
    } // namespace details

} // namespace nn::sl

#endif