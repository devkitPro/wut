#include <coreinit/debug.h>
#include <nn/sl/ILaunchedTitleListAccessor.h>

namespace nn::sl {

    namespace {
        extern "C" details::ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(LaunchedTitleListAccessorType type);
        extern "C" details::ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFv();
    } // namespace
    static details::LaunchedTitleListAccessorFromPtr sDefaultLaunchedTitleListAccessorType0(GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(TITLE_LIST_ACCESSOR_LAUNCHED_TITLES));
    static details::LaunchedTitleListAccessorFromPtr sDefaultLaunchedTitleListAccessorType1(GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(TITLE_LIST_ACCESSOR_PLAY_STATS));

    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor(LaunchedTitleListAccessorType type) {
        if (type == TITLE_LIST_ACCESSOR_LAUNCHED_TITLES) {
            return sDefaultLaunchedTitleListAccessorType0;
        } else if (type == TITLE_LIST_ACCESSOR_PLAY_STATS) {
            return sDefaultLaunchedTitleListAccessorType1;
        }
        OSFatal("Called GetDefaultLaunchedTitleListAccessor with invalid type");
        // not reached
        return sDefaultLaunchedTitleListAccessorType1;
    }
    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor() {
        return sDefaultLaunchedTitleListAccessorType0;
    }
} // namespace nn::sl