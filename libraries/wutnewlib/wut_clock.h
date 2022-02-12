#pragma once

// The Wii U epoch is at 2000, so we must map it to 1970 for gettime
#define WIIU_EPOCH_YEAR                (2000)

#define EPOCH_YEAR                     (1970)
#define EPOCH_YEARS_SINCE_LEAP         2
#define EPOCH_YEARS_SINCE_CENTURY      70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define EPOCH_DIFF_YEARS               (2000 - EPOCH_YEAR)
#define EPOCH_DIFF_DAYS                                        \
   ((EPOCH_DIFF_YEARS * 365) +                                 \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_LEAP) / 4 -      \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_CENTURY) / 100 + \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_LEAP_CENTURY) / 400)
#define EPOCH_DIFF_SECS (60ull * 60ull * 24ull * (uint64_t) EPOCH_DIFF_DAYS)
