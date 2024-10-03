#pragma once

// The Wii U OSTime epoch is at 2000, so we must map it to 1970 for gettime
#define WIIU_OSTIME_EPOCH_YEAR         (2000)
// The Wii U FSTime epoch is at 1980, so we must map it to 1970 for gettime
#define WIIU_FSTIME_EPOCH_YEAR         (1980)

#define EPOCH_YEAR                     (1970)
#define EPOCH_YEARS_SINCE_LEAP         2
#define EPOCH_YEARS_SINCE_CENTURY      70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define EPOCH_DIFF_YEARS(year)         (year - EPOCH_YEAR)
#define EPOCH_DIFF_DAYS(year)                                        \
   ((EPOCH_DIFF_YEARS(year) * 365) +                                 \
    (EPOCH_DIFF_YEARS(year) - 1 + EPOCH_YEARS_SINCE_LEAP) / 4 -      \
    (EPOCH_DIFF_YEARS(year) - 1 + EPOCH_YEARS_SINCE_CENTURY) / 100 + \
    (EPOCH_DIFF_YEARS(year) - 1 + EPOCH_YEARS_SINCE_LEAP_CENTURY) / 400)
#define EPOCH_DIFF_SECS(year) (60ull * 60ull * 24ull * (uint64_t)EPOCH_DIFF_DAYS(year))
