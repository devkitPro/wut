#pragma once

#include "KillerNotification.h"
#include "sl_cpp.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED KillerNotificationSelectorInternal {
            void *launchedTitleListAccessor;
            void *killerNotificationAccessor;
            void *titleListCache;
            void *killerNotificationSerializer;
            void *settingsAccessor;
            void *accountInfoAccessor;
            void *timeAccessor;
            void *killerNotificationTransferRecordManager;
            void *vtable;
        } KillerNotificationSelectorInternal;
        WUT_CHECK_SIZE(KillerNotificationSelectorInternal, 0x24);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x00, launchedTitleListAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x04, killerNotificationAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x08, titleListCache);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x0C, killerNotificationSerializer);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x10, settingsAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x14, accountInfoAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x18, timeAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x1C, killerNotificationTransferRecordManager);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x20, vtable);

        extern "C" KillerNotificationSelectorInternal *__ct__Q3_2nn2sl26KillerNotificationSelectorFv(KillerNotificationSelectorInternal *);
        extern "C" void __dt__Q3_2nn2sl26KillerNotificationSelectorFv(KillerNotificationSelectorInternal *, int);
        extern "C" nn::Result Select__Q3_2nn2sl26KillerNotificationSelectorFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfoPb(KillerNotificationSelectorInternal *, KillerNotification *, TitleInfo *, bool *);
    } // namespace details

    class KillerNotificationSelector {
    public:
        KillerNotificationSelector() {
            __ct__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance);
        }

        ~KillerNotificationSelector() {
            __dt__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance, 2);
        }

        nn::Result Select(KillerNotification *u1, TitleInfo *u2, bool *u3) {
            return Select__Q3_2nn2sl26KillerNotificationSelectorFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfoPb(&mInstance, u1, u2, u3);
        }

    private:
        details::KillerNotificationSelectorInternal mInstance = {};
    };
} // namespace nn::sl

#endif