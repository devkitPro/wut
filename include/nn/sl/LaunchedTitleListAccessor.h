#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ILaunchedTitleListAccessor;
    namespace details {
        struct ILaunchedTitleListAccessorInternal;

        typedef nn::Result (*ILaunchedTitleListAccessor_GetByAccountFn)(ILaunchedTitleListAccessorInternal *, TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId);

        struct WUT_PACKED ILaunchedTitleListAccessorInternalVTable {
            ILaunchedTitleListAccessor *instance; // normally this is padding
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

        extern "C" ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(int);
        extern "C" ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFv();
    } // namespace details

    class ILaunchedTitleListAccessor {
        friend class DataCreator;
        friend class KillerNotificationSelector;

    public:
        ILaunchedTitleListAccessor()          = default;
        virtual ~ILaunchedTitleListAccessor() = default;

        virtual nn::Result GetByAccount(TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) = 0;

    private:
        virtual details::ILaunchedTitleListAccessorInternal *GetInternal() = 0;
    };

    class ILaunchedTitleListAccessorBase : public ILaunchedTitleListAccessor {

    public:
        ILaunchedTitleListAccessorBase() {
            InitInternalVtable();
        }

        ILaunchedTitleListAccessorBase(ILaunchedTitleListAccessorBase &src) {
            InitInternalVtable();
        }

        ILaunchedTitleListAccessorBase &operator=(const ILaunchedTitleListAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        ILaunchedTitleListAccessorBase &operator=(ILaunchedTitleListAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ILaunchedTitleListAccessorBase() override = default;

    private:
        static nn::Result GetByAccountWrapper(details::ILaunchedTitleListAccessorInternal *instance, TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) {
            return instance->vtable->instance->GetByAccount(outTitleInfos, outTitleInfoSize, inTitleInfosSize, userId);
        }

        details::ILaunchedTitleListAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance       = this,
                                .GetByAccountFn = &GetByAccountWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ILaunchedTitleListAccessorInternal mInstance{};
        details::ILaunchedTitleListAccessorInternalVTable mVTable{};
    };


    class LaunchedTitleListAccessorFromPtr : public ILaunchedTitleListAccessor {
    public:
        explicit LaunchedTitleListAccessorFromPtr(details::ILaunchedTitleListAccessorInternal *ptr) : mInstancePtr(ptr) {
        }

        nn::Result GetByAccount(TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) override {
            return mInstancePtr->vtable->GetByAccountFn(mInstancePtr, outTitleInfos, outTitleInfoSize, inTitleInfosSize, userId);
        }

        details::ILaunchedTitleListAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

    private:
        details::ILaunchedTitleListAccessorInternal *mInstancePtr;
    };

    enum LaunchedTitleListAccessorType {
        TITLE_LIST_ACCESSOR_LAUNCHED_TITLES = 0,
        TITLE_LIST_ACCESSOR_PLAY_STATS      = 1,
    };

    LaunchedTitleListAccessorFromPtr GetDefaultLaunchedTitleListAccessor(LaunchedTitleListAccessorType type) {
        return LaunchedTitleListAccessorFromPtr(details::GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(type));
    }
    LaunchedTitleListAccessorFromPtr GetDefaultLaunchedTitleListAccessor() {
        return LaunchedTitleListAccessorFromPtr(details::GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif