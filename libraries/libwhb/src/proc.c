#include <coreinit/core.h>
#include <coreinit/exit.h>
#include <coreinit/foreground.h>
#include <coreinit/messagequeue.h>
#include <coreinit/systeminfo.h>
#include <coreinit/title.h>
#include <gx2/event.h>
#include <proc_ui/procui.h>
#include <sysapp/launch.h>
#include <whb/log.h>
#include <whb/proc.h>

#define HBL_TITLE_ID           (0x0005000013374842)
#define MII_MAKER_JPN_TITLE_ID (0x000500101004A000)
#define MII_MAKER_USA_TITLE_ID (0x000500101004A100)
#define MII_MAKER_EUR_TITLE_ID (0x000500101004A200)

static uint32_t
        sMainCore;

static BOOL
        sRunning = FALSE;

static BOOL
        sFromHBL = FALSE;

static uint32_t
procSaveCallback(void *context)
{
   OSSavesDone_ReadyToRelease();
   return 0;
}


static uint32_t
procHomeButtonDenied(void *context)
{
   if (sFromHBL) {
      WHBProcStopRunning();
   }

   return 0;
}

void WHBProcInit()
{
   uint64_t titleID = OSGetTitleID();

   // Homebrew Launcher does not like the standard ProcUI application loop,
   // so instead we disable the home buttom menu and use the home button
   // to trigger an exit.
   if (titleID == HBL_TITLE_ID ||
       titleID == MII_MAKER_JPN_TITLE_ID ||
       titleID == MII_MAKER_USA_TITLE_ID ||
       titleID == MII_MAKER_EUR_TITLE_ID) {
      // Important: OSEnableHomeButtonMenu must come before ProcUIInitEx.
      OSEnableHomeButtonMenu(FALSE);
      sFromHBL = TRUE;
   }

   sMainCore = OSGetCoreId();
   sRunning  = TRUE;
   ProcUIInitEx(&procSaveCallback, NULL);

   if (sFromHBL) {
      ProcUIRegisterCallback(PROCUI_CALLBACK_HOME_BUTTON_DENIED,
                             &procHomeButtonDenied, NULL, 100);
   }
}

void WHBProcShutdown()
{
   sRunning = FALSE;

   // If we're running from Homebrew Launcher we must do a SYSRelaunchTitle to
   // correctly return to HBL.
   if (sFromHBL) {
      SYSRelaunchTitle(0, NULL);
   }
}

void WHBProcStopRunning()
{
   sRunning = FALSE;
}

BOOL WHBProcIsRunning()
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
      ProcUIShutdown();
   }

   return sRunning;
}
