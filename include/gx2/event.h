#pragma once
#include <wut.h>
#include <coreinit/time.h>

/**
 * \defgroup gx2_event Event
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2DisplayListOverrunData GX2DisplayListOverrunData;

typedef enum GX2EventType
{
   GX2_EVENT_TYPE_VSYNC                   = 2,
   GX2_EVENT_TYPE_FLIP                    = 3,
   GX2_EVENT_TYPE_DISPLAY_LIST_OVERRUN    = 4,
} GX2EventType;

typedef void (*GX2EventCallbackFunction)(GX2EventType, void *);

struct GX2DisplayListOverrunData
{
   void *oldList;
   uint32_t oldSize;
   void *newList;
   uint32_t newSize;
   UNKNOWN(8);
};
CHECK_OFFSET(GX2DisplayListOverrunData, 0x00, oldList);
CHECK_OFFSET(GX2DisplayListOverrunData, 0x04, oldSize);
CHECK_OFFSET(GX2DisplayListOverrunData, 0x08, newList);
CHECK_OFFSET(GX2DisplayListOverrunData, 0x0C, newSize);
CHECK_SIZE(GX2DisplayListOverrunData, 0x18);

BOOL
GX2DrawDone();

void
GX2WaitForVsync();

void
GX2WaitForFlip();

void
GX2SetEventCallback(GX2EventType type,
                    GX2EventCallbackFunction func,
                    void *userData);

void
GX2GetEventCallback(GX2EventType type,
                    GX2EventCallbackFunction *funcOut,
                    void **userDataOut);

OSTime
GX2GetRetiredTimeStamp();

OSTime
GX2GetLastSubmittedTimeStamp();

BOOL
GX2WaitTimeStamp(OSTime time);

void
GX2GetSwapStatus(uint32_t *swapCount,
                 uint32_t *flipCount,
                 OSTime *lastFlip,
                 OSTime *lastVsync);

#ifdef __cplusplus
}
#endif

/** @} */
