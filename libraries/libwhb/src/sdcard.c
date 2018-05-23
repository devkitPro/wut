#include <coreinit/filesystem.h>
#include <whb/sdcard.h>
#include <whb/log.h>

static BOOL
sMounted = FALSE;

static char
sMountPath[128] = { 0 };

static FSClient
sClient;

BOOL
WHBMountSdCard()
{
   FSCmdBlock cmd;
   FSMountSource mountSource;
   FSStatus result;

   if (sMounted) {
      return TRUE;
   }

   FSInit();

   result = FSAddClient(&sClient, -1);
   if (result != FS_STATUS_OK) {
      WHBLogPrintf("%s: FSAddClient error %d", __FUNCTION__, result);
      return FALSE;
   }

   FSInitCmdBlock(&cmd);
   result = FSGetMountSource(&sClient, &cmd, FS_MOUNT_SOURCE_SD, &mountSource, -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSGetMountSource error %d", __FUNCTION__, result);
      goto fail;
   }

   result = FSMount(&sClient, &cmd, &mountSource, sMountPath, sizeof(sMountPath), -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSMount error %d", __FUNCTION__, result);
      goto fail;
   }

   sMounted = TRUE;
   return TRUE;

fail:
   FSDelClient(&sClient, -1);
   return FALSE;
}

char *
WHBGetSdCardMountPath()
{
   return sMountPath;
}

BOOL
WHBUnmountSdCard()
{
   FSCmdBlock cmd;
   FSStatus result;

   if (!sMounted) {
      return TRUE;
   }

   FSInitCmdBlock(&cmd);

   result = FSUnmount(&sClient, &cmd, sMountPath, -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSUnmount error %d", __FUNCTION__, result);
      return FALSE;
   }

   sMounted = FALSE;
   return TRUE;
}
