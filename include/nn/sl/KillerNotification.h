#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/KillerNotification.h>
#include "sl_cpp.h"

#ifdef __cplusplus

namespace nn::sl
{
struct KillerNotification;
namespace details
{
extern "C" nn::Result
__CPR81__CheckEmptyValue__Q3_2nn2sl18KillerNotificationSFPbPCQ3_2nn2slJ26J(bool *u1, const KillerNotification *u2);
extern "C" void
__CPR76__GetEmptyValue__Q3_2nn2sl18KillerNotificationSFPQ3_2nn2slJ24J(KillerNotification *u1);
} // namespace details

typedef enum KillerNotificationType
{
   PROMOTION      = 0,
   PUSH_APP       = 1,
   NON_COMMERCIAL = 2
} KillerNotificationType;

typedef enum KillerNotificationNotificationPattern
{
   NORMAL = 0,
   SILENT = 1
} KillerNotificationNotificationPattern;

typedef enum KillerNotificationGender
{
   UNKNOWN = 0,
   MALE    = 1,
   FEMALE  = 2
} KillerNotificationGender;

typedef enum KillerNotificationAllowLocalAccount : int8_t
{
   ALLOW     = 0,
   NOT_ALLOW = 1
} KillerNotificationAllowLocalAccount;

typedef enum KillerNotificationAccountMailActivation : int8_t
{
   NOT_ACTIVATED = 0,
   ANYBODY       = 1
} KillerNotificationAccountMailActivation;

typedef enum KillerNotificationConjunction
{
   AND = 0,
   OR  = 1
} KillerNotificationConjunction;

struct WUT_PACKED KillerNotificationInstalledTitleFilter
{
   uint64_t titleId;
   KillerNotificationConjunction conjunction;
};
WUT_CHECK_SIZE(KillerNotificationInstalledTitleFilter, 0x0C);
WUT_CHECK_OFFSET(KillerNotificationInstalledTitleFilter, 0x00, titleId);
WUT_CHECK_OFFSET(KillerNotificationInstalledTitleFilter, 0x08, conjunction);

struct WUT_PACKED KillerNotificationPlayedTitleFilter
{
   uint64_t titleId;
   enum KillerNotificationConjunction conjunction;
};
WUT_CHECK_SIZE(KillerNotificationPlayedTitleFilter, 0x0C);
WUT_CHECK_OFFSET(KillerNotificationPlayedTitleFilter, 0x00, titleId);
WUT_CHECK_OFFSET(KillerNotificationPlayedTitleFilter, 0x08, conjunction);

struct WUT_PACKED KillerNotificationTitleFilter
{
   uint64_t titleId;
   WUT_UNKNOWN_BYTES(4);
   int32_t played;
   WUT_UNKNOWN_BYTES(4);
   int32_t installed;
};
WUT_CHECK_SIZE(KillerNotificationTitleFilter, 0x18);
WUT_CHECK_OFFSET(KillerNotificationTitleFilter, 0x0C, played);
WUT_CHECK_OFFSET(KillerNotificationTitleFilter, 0x14, installed);


struct WUT_PACKED KillerNotification
{
   uint32_t serialId;
   uint32_t version;
   WUT_UNKNOWN_BYTES(16);
   bool deleteFlag;
   char language[4];
   WUT_UNKNOWN_BYTES(3);
   KillerNotificationType type;
   KillerNotificationNotificationPattern notificationPattern;
   struct
   {
      uint64_t titleId;
      char parameter[2048];
   } launchApplication;
   uint32_t priority;
   struct
   {
      struct
      {
         DRCImagePalette palette;  // the "main" image actually uses the button palette in the quick start menu
         uint8_t pixels[400][854]; // index of color in (button) palette - 854x400
      } main;
      struct
      {
         DRCImagePalette palette;
         uint8_t pixels[160][487]; // index of color in palette - 487*160
      } button;
      WUT_PADDING_BYTES(0);
      char banner[290416]; // BMP! 854×85, Bit depth: 32
   } images;
   struct
   {
      WUT_UNKNOWN_BYTES(12);
      struct WUT_PACKED
      {
         uint64_t startUnixTime;
         uint64_t endUnixTime;
      } duration;
      WUT_UNKNOWN_BYTES(4);
      uint32_t lifetime;
      WUT_UNKNOWN_BYTES(4);
      struct
      {
         struct
         {
            uint32_t lowerBound;
            uint32_t upperBound;
         } age;
         KillerNotificationGender gender;
      } account;
      struct
      {
         uint32_t titleCount;
         WUT_UNKNOWN_BYTES(4);
         KillerNotificationTitleFilter titles[2];
      } titleFilter;
      WUT_UNKNOWN_BYTES(1);
      struct WUT_PACKED
      {
         KillerNotificationAllowLocalAccount allowLocalAccount;
         WUT_UNKNOWN_BYTES(2);
         uint32_t ageRestrictionLowerBound;
      } ageRestriction;
      KillerNotificationAccountMailActivation accountMailActivation;

      WUT_UNKNOWN_BYTES(11);
      uint32_t accountBirthMonth;
      WUT_UNKNOWN_BYTES(4);
      int8_t anticipatoryDownload;
      WUT_UNKNOWN_BYTES(15);
      struct
      {
         int32_t installedTitleCount;
         enum KillerNotificationConjunction installedConjunction;
         WUT_UNKNOWN_BYTES(4);
         struct KillerNotificationInstalledTitleFilter installedTitleFilter[2];
      };
      WUT_UNKNOWN_BYTES(12);
      struct
      {
         uint32_t playedTitleFilterCount;
         enum KillerNotificationConjunction playedConjunction;
         WUT_UNKNOWN_BYTES(4);
         uint32_t played_duration_sinceUnixTime;
         WUT_UNKNOWN_BYTES(4);
         KillerNotificationPlayedTitleFilter playedTitleFilter[2];
      };
   } displayCondition;
   WUT_UNKNOWN_BYTES(8);
   uint32_t formatVersion;
   uint32_t tags;
   WUT_UNKNOWN_BYTES(256);

   static nn::Result
   CheckEmptyValue(bool *outRes, const KillerNotification *u2)
   {
      return details::__CPR81__CheckEmptyValue__Q3_2nn2sl18KillerNotificationSFPbPCQ3_2nn2slJ26J(outRes, u2);
   }

   static void
   GetEmptyValue(KillerNotification *u1)
   {
      return details::__CPR76__GetEmptyValue__Q3_2nn2sl18KillerNotificationSFPQ3_2nn2slJ24J(u1);
   }
};
WUT_CHECK_SIZE(KillerNotification, 0xae768);
WUT_CHECK_OFFSET(KillerNotification, 0x0, serialId);
WUT_CHECK_OFFSET(KillerNotification, 0x04, version);
WUT_CHECK_OFFSET(KillerNotification, 0x18, deleteFlag);
WUT_CHECK_OFFSET(KillerNotification, 0x20, type);
WUT_CHECK_OFFSET(KillerNotification, 0x24, notificationPattern);
WUT_CHECK_OFFSET(KillerNotification, 0x28, launchApplication.titleId);
WUT_CHECK_OFFSET(KillerNotification, 0x30, launchApplication.parameter);
WUT_CHECK_OFFSET(KillerNotification, 0x830, priority);
WUT_CHECK_OFFSET(KillerNotification, 0x834, images);
WUT_CHECK_OFFSET(KillerNotification, 0x834, images.main);
WUT_CHECK_OFFSET(KillerNotification, 0x834 + 0x400, images.main.pixels);
WUT_CHECK_OFFSET(KillerNotification, 0x54294, images.button);
WUT_CHECK_OFFSET(KillerNotification, 0x54294 + 0x400, images.button.pixels);
WUT_CHECK_OFFSET(KillerNotification, 0x676f4, images.banner);
WUT_CHECK_OFFSET(KillerNotification, 0xae570, displayCondition.duration.startUnixTime);
WUT_CHECK_OFFSET(KillerNotification, 0xae578, displayCondition.duration.endUnixTime);
WUT_CHECK_OFFSET(KillerNotification, 0xae584, displayCondition.lifetime);
WUT_CHECK_OFFSET(KillerNotification, 0xae58C, displayCondition.account.age.lowerBound);
WUT_CHECK_OFFSET(KillerNotification, 0xae590, displayCondition.account.age.upperBound);
WUT_CHECK_OFFSET(KillerNotification, 0xae594, displayCondition.account.gender);
WUT_CHECK_OFFSET(KillerNotification, 0xae598, displayCondition.titleFilter.titleCount);
WUT_CHECK_OFFSET(KillerNotification, 0xae5a0, displayCondition.titleFilter.titles);
WUT_CHECK_OFFSET(KillerNotification, 0xae5d1, displayCondition.ageRestriction.allowLocalAccount);
WUT_CHECK_OFFSET(KillerNotification, 0xae5d4, displayCondition.ageRestriction.ageRestrictionLowerBound);
WUT_CHECK_OFFSET(KillerNotification, 0xae5d8, displayCondition.accountMailActivation);
WUT_CHECK_OFFSET(KillerNotification, 0xae5e4, displayCondition.accountBirthMonth);
WUT_CHECK_OFFSET(KillerNotification, 0xae5ec, displayCondition.anticipatoryDownload);
WUT_CHECK_OFFSET(KillerNotification, 0xae5fc, displayCondition.installedTitleCount);
WUT_CHECK_OFFSET(KillerNotification, 0xae600, displayCondition.installedConjunction);
WUT_CHECK_OFFSET(KillerNotification, 0xae608, displayCondition.installedTitleFilter);
WUT_CHECK_OFFSET(KillerNotification, 0xae62c, displayCondition.playedTitleFilterCount);
WUT_CHECK_OFFSET(KillerNotification, 0xae630, displayCondition.playedConjunction);
WUT_CHECK_OFFSET(KillerNotification, 0xae638, displayCondition.played_duration_sinceUnixTime);
WUT_CHECK_OFFSET(KillerNotification, 0xae640, displayCondition.playedTitleFilter);
WUT_CHECK_OFFSET(KillerNotification, 0xae660, formatVersion);
WUT_CHECK_OFFSET(KillerNotification, 0xae664, tags);

} // namespace nn::sl

#endif