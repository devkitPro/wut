#pragma once

#include "KillerNotification.h"
#include "TitleInfo.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace {
        typedef struct WUT_PACKED CacheManagerInternal {
            void *quickStartTitleInfoSerializer;
            void *killerNotificationSerializer;
            void *jumpTitleInfoSerializer;
        } CacheManagerInternal;
        WUT_CHECK_SIZE(CacheManagerInternal, 0x0c);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x00, quickStartTitleInfoSerializer);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x04, killerNotificationSerializer);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x08, jumpTitleInfoSerializer);

        extern "C" CacheManagerInternal *__ct__Q3_2nn2sl11DataCreatorFv(CacheManagerInternal *);
        extern "C" void SetupInitialCache__Q3_2nn2sl12CacheManagerFv(CacheManagerInternal *);
        extern "C" nn::Result GetKillerNotificationCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfo(CacheManagerInternal *, KillerNotification *, TitleInfo *);
        extern "C" nn::Result GetQuickStartCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoi(CacheManagerInternal *, TitleInfo *, int);
        extern "C" nn::Result Get__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoiPQ3_2nn2sl18KillerNotificationT1(CacheManagerInternal *, TitleInfo *, int, KillerNotification *, TitleInfo *);
    } // namespace

    class CacheManager {
    public:
        CacheManager() {
            __ct__Q3_2nn2sl11DataCreatorFv(&instance);
        }
        void SetupInitialCache() {
            SetupInitialCache__Q3_2nn2sl12CacheManagerFv(&instance);
        }

        nn::Result GetKillerNotificationCache(KillerNotification *u1, TitleInfo *u2) {
            return GetKillerNotificationCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfo(&instance, u1, u2);
        }

        nn::Result GetQuickStartCache(TitleInfo *u1, int u2) {
            return GetQuickStartCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoi(&instance, u1, u2);
        }

        nn::Result Get(TitleInfo *u1, int u2, KillerNotification *u3, TitleInfo *u4) {
            return Get__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoiPQ3_2nn2sl18KillerNotificationT1(&instance, u1, u2, u3, u4);
        }

        ~CacheManager() = default;

    private:
        CacheManagerInternal instance{};
    };
} // namespace nn::sl

#endif