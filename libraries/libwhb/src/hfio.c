#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <string.h>
#include <whb/hfio.h>
#include <whb/log.h>


static BOOL
   sHFIOMounted = FALSE;

static char
   sHFIOMountPath[128] = {0};

static FSClient
   sHFIOClient;

BOOL
WHBMountHostFileIO()
{
   FSCmdBlock cmd;
   FSMountSource mountSource;
   FSStatus result;

   if (sHFIOMounted) {
      return TRUE;
   }

   FSInit();

   result = FSAddClient(&sHFIOClient, FS_ERROR_FLAG_ALL);
   if (result != FS_STATUS_OK) {
      WHBLogPrintf("%s: FSAddClient error %d", __FUNCTION__, result);
      return FALSE;
   }

   FSInitCmdBlock(&cmd);
   result = FSGetMountSource(&sHFIOClient, &cmd, FS_MOUNT_SOURCE_HFIO, &mountSource, FS_ERROR_FLAG_ALL);
   if (result < 0) {
      WHBLogPrintf("%s: FSGetMountSource error %d", __FUNCTION__, result);
      goto fail;
   }

   result = FSMount(&sHFIOClient, &cmd, &mountSource, sHFIOMountPath, sizeof(sHFIOMountPath), FS_ERROR_FLAG_ALL);
   if (result < 0) {
      WHBLogPrintf("%s: FSMount error %d", __FUNCTION__, result);
      goto fail;
   }

   sHFIOMounted = TRUE;
   return TRUE;

fail:
   FSDelClient(&sHFIOClient, FS_ERROR_FLAG_ALL);
   return FALSE;
}

char *
WHBGetHostFileIOMountPath()
{
   return sHFIOMountPath;
}

char *
WHBPathForWellKnownHostDirectory(WHBWellKnownHostDirectory directory)
{
   // The host path is 128 bytes, and the maximum we can append is 15 bytes, for a final size of 143.
   char *finalPath = (char *)MEMAllocFromDefaultHeap(143);
   if (finalPath == NULL) {
      return NULL;
   }

   // Ensure we get a NULL terminator, mimic calloc.
   memset(finalPath, 0, 143);
   strcat(finalPath, sHFIOMountPath);
   strcat(finalPath, "/");
   switch (directory) {
      case WHB_MLC_HOST_DIRECTORY:
         strcat(finalPath, "%MLC_EMU_DIR");
         break;
      case WHB_SLC_HOST_DIRECTORY:
         strcat(finalPath, "%SLC_EMU_DIR");
         break;
      case WHB_DISC_HOST_DIRECTORY:
         strcat(finalPath, "%DISC_EMU_DIR");
         break;
      case WHB_SAVE_HOST_DIRECTORY:
         strcat(finalPath, "%SAVE_EMU_DIR");
         break;
      case WHB_NETWORK_DRIVE_HOST_DIRECTORY:
         strcat(finalPath, "%NETWORK");
         break;
   }
   return finalPath;
}

BOOL
WHBUnmountHostFileIO()
{
   FSCmdBlock cmd;
   FSStatus result;

   if (!sHFIOMounted) {
      return TRUE;
   }

   FSInitCmdBlock(&cmd);

   result = FSUnmount(&sHFIOClient, &cmd, sHFIOMountPath, FS_ERROR_FLAG_ALL);
   if (result < 0) {
      WHBLogPrintf("%s: FSUnmount error %d", __FUNCTION__, result);
      return FALSE;
   }

   result = FSDelClient(&sHFIOClient, FS_ERROR_FLAG_ALL);
   if (result < 0) {
      WHBLogPrintf("%s: FSDelClient error %d", __FUNCTION__, result);
      return FALSE;
   }

   sHFIOMounted = FALSE;
   return TRUE;
}
