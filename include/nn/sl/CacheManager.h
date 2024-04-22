#pragma once

#include <nn/result.h>
#include <nn/sl/ISerializer.h>
#include <nn/sl/KillerNotification.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED CacheManagerInternal {
            ISerializerInternal *quickStartTitleInfoSerializer;
            ISerializerInternal *killerNotificationSerializer;
            ISerializerInternal *jumpTitleInfoSerializer;
        } CacheManagerInternal;
        WUT_CHECK_SIZE(CacheManagerInternal, 0x0c);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x00, quickStartTitleInfoSerializer);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x04, killerNotificationSerializer);
        WUT_CHECK_OFFSET(CacheManagerInternal, 0x08, jumpTitleInfoSerializer);

        extern "C" CacheManagerInternal *__ct__Q3_2nn2sl12CacheManagerFv(CacheManagerInternal *);
        extern "C" void SetupInitialCache__Q3_2nn2sl12CacheManagerFv(CacheManagerInternal *);
        extern "C" nn::Result GetKillerNotificationCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfo(CacheManagerInternal *, KillerNotification *, TitleInfo *);
        extern "C" nn::Result GetQuickStartCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoi(CacheManagerInternal *, TitleInfo *, int);
        extern "C" nn::Result Get__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoiPQ3_2nn2sl18KillerNotificationT1(CacheManagerInternal *, TitleInfo *, int, KillerNotification *, TitleInfo *);
        extern "C" nn::Result Initialize__Q3_2nn2sl12CacheManagerFRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfoRQ3_2nn2sl49ISerializer__tm__30_Q3_2nn2sl18KillerNotificationT1(
                CacheManagerInternal *,
                ISerializerInternal *,
                ISerializerInternal *,
                ISerializerInternal *);
    } // namespace details

    class CacheManager {
    public:
        CacheManager() : mQuickStartTitleInfoSerializer(nullptr),
                         mKillerNotificationSerializer(nullptr),
                         mJumpTitleInfoSerializer(nullptr) {
            if (__ct__Q3_2nn2sl12CacheManagerFv(&mInstance) != nullptr) {
                mQuickStartTitleInfoSerializer = details::SerializerFromPtr<TitleInfo>(mInstance.quickStartTitleInfoSerializer);
                mKillerNotificationSerializer  = details::SerializerFromPtr<KillerNotification>(mInstance.killerNotificationSerializer);
                mJumpTitleInfoSerializer       = details::SerializerFromPtr<TitleInfo>(mInstance.jumpTitleInfoSerializer);
            }
        }

        [[nodiscard]] details::ISerializerBase<TitleInfo> &GetQuickStartTitleInfoSerializer() {
            return mQuickStartTitleInfoSerializer;
        }

        [[nodiscard]] details::ISerializerBase<KillerNotification> &GetKillerNotificationSerializer() {
            return mKillerNotificationSerializer;
        }

        [[nodiscard]] details::ISerializerBase<TitleInfo> &GetJumpTitleInfoSerializer() {
            return mJumpTitleInfoSerializer;
        }

        void SetupInitialCache() {
            SetupInitialCache__Q3_2nn2sl12CacheManagerFv(&mInstance);
        }

        nn::Result GetKillerNotificationCache(KillerNotification *u1, TitleInfo *u2) {
            return GetKillerNotificationCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfo(&mInstance, u1, u2);
        }

        nn::Result GetQuickStartCache(TitleInfo *u1, int u2) {
            return GetQuickStartCache__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoi(&mInstance, u1, u2);
        }

        nn::Result Get(TitleInfo *u1, int u2, KillerNotification *u3, TitleInfo *u4) {
            return Get__Q3_2nn2sl12CacheManagerFPQ3_2nn2sl9TitleInfoiPQ3_2nn2sl18KillerNotificationT1(&mInstance, u1, u2, u3, u4);
        }

        void Initialize(details::ISerializerBase<TitleInfo> &quickStartTitleInfoSerializer, details::ISerializerBase<KillerNotification> &killerNotificationSerializer, details::ISerializerBase<TitleInfo> &jumpTitleInfoSerializer) {
            Initialize__Q3_2nn2sl12CacheManagerFRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfoRQ3_2nn2sl49ISerializer__tm__30_Q3_2nn2sl18KillerNotificationT1(&mInstance,
                                                                                                                                                                   quickStartTitleInfoSerializer.GetInternal(),
                                                                                                                                                                   killerNotificationSerializer.GetInternal(),
                                                                                                                                                                   jumpTitleInfoSerializer.GetInternal());
            mQuickStartTitleInfoSerializer = details::SerializerFromPtr<TitleInfo>(quickStartTitleInfoSerializer.GetInternal());
            mKillerNotificationSerializer  = details::SerializerFromPtr<KillerNotification>(killerNotificationSerializer.GetInternal());
            mJumpTitleInfoSerializer       = details::SerializerFromPtr<TitleInfo>(jumpTitleInfoSerializer.GetInternal());
        }

        ~CacheManager() = default;

    private:
        details::CacheManagerInternal mInstance{};
        details::SerializerFromPtr<TitleInfo> mQuickStartTitleInfoSerializer;
        details::SerializerFromPtr<KillerNotification> mKillerNotificationSerializer;
        details::SerializerFromPtr<TitleInfo> mJumpTitleInfoSerializer;
    };
} // namespace nn::sl

#endif