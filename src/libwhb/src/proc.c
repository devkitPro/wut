#include <whb/proc.h>
#include <coreinit/core.h>
#include <coreinit/foreground.h>
#include <gx2/event.h>
#include <proc_ui/procui.h>

static uint32_t
sMainCore;

static BOOL
sRunning = FALSE;

static ProcUICallback
sAcquireCallback = NULL;

static uint32_t
ProcSaveCallback(void *context)
{
   OSSavesDone_ReadyToRelease();
   return 0;
}

void
WHBProcInit()
{
   sMainCore = OSGetCoreId();
   sRunning = TRUE;
   ProcUIInitEx(&ProcSaveCallback, NULL);
}

void
WHBProcShutdown()
{
   sRunning = FALSE;
}

void
WHBProcStopRunning()
{
   sRunning = FALSE;
}

BOOL
WHBProcIsRunning()
{
   ProcUIStatus status;

   if (sMainCore != OSGetCoreId()) {
      ProcUISubProcessMessages(TRUE);
      return sRunning;
   }

   status = ProcUIProcessMessages(TRUE);
   if (status == PROCUI_STATUS_EXITING) {
      WHBProcStopRunning();
   } else if (status == PROCUI_STATUS_RELEASE_FOREGROUND) {
      ProcUIDrawDoneRelease();
   }

   if (!sRunning) {
      GX2DrawDone();
      ProcUIShutdown();
   }

   return sRunning;
}
