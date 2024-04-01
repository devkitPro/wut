#pragma once

namespace nn::sl {
    namespace {
        typedef struct WUT_PACKED QuickStartApplicationSelectorInternal {
            void *preferentialTitleAccessor;
            void *defaultTitleAccessor;
            void *whiteListAccessor;
            void *titleListCache;
            void *settingsAccessor;
            void *blackListAccessor;
            void *vtable;
        } QuickStartApplicationSelectorInternal;
        WUT_CHECK_SIZE(QuickStartApplicationSelectorInternal, 0x1C);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x00, preferentialTitleAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x04, defaultTitleAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x08, whiteListAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x0C, titleListCache);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x10, settingsAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x14, blackListAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x18, vtable);

        extern "C" QuickStartApplicationSelectorInternal *__ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(QuickStartApplicationSelectorInternal *);
        extern "C" nn::Result Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(QuickStartApplicationSelectorInternal *, TitleInfo *, int);
    } // namespace

    class QuickStartApplicationSelector {
    public:
        QuickStartApplicationSelector() {
            __ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(&mInstance);
        }

        ~QuickStartApplicationSelector() = default;

        nn::Result Select(TitleInfo *u1, int u2) {
            return Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(&mInstance, u1, u2);
        }

    private:
        QuickStartApplicationSelectorInternal mInstance = {};
    };
} // namespace nn::sl