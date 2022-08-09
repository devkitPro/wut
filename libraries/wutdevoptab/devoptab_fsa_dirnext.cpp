#include "devoptab_fsa.h"
#include <mutex>
#include <sys/syslimits.h>

int
__wut_fsa_dirnext(struct _reent *r,
                  DIR_ITER *dirState,
                  char *filename,
                  struct stat *filestat) {
   FSError status;
   __wut_fsa_dir_t *dir;
   __wut_fsa_device_t *deviceData;

   if (!dirState || !filename || !filestat) {
      r->_errno = EINVAL;
      return -1;
   }

   deviceData = (__wut_fsa_device_t *) r->deviceData;
   dir = (__wut_fsa_dir_t *) (dirState->dirStruct);

   std::scoped_lock lock(dir->mutex);
   memset(&dir->entry_data, 0, sizeof(dir->entry_data));

   status = FSAReadDir(deviceData->clientHandle, dir->fd, &dir->entry_data);
   if (status < 0) {
      if (status != FS_ERROR_END_OF_DIR) {
         WUT_DEBUG_REPORT("FSAReadDir(0x%08X, 0x%08X, 0x%08X) (%s) failed: %s\n",
                          deviceData->clientHandle, dir->fd, &dir->entry_data, dir->fullPath, FSAGetStatusStr(status));
      }
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   ino_t ino;
   size_t fullLen = strlen(dir->fullPath) + 1 + strlen(dir->entry_data.name) + 1;
   char *fullStr = (char *) memalign(0x40, fullLen);
   if (fullStr) {
      if (snprintf(fullStr, fullLen, "%s/%s", dir->fullPath, dir->entry_data.name) >= (int) fullLen) {
         WUT_DEBUG_REPORT("__wut_fsa_dirnext: snprintf fullStr result was truncated\n");
      }
      ino = __wut_fsa_hashstring(fullStr);
      free(fullStr);
   } else {
      ino = 0;
      WUT_DEBUG_REPORT("__wut_fsa_dirnext: Failed to allocate memory for fullStr. st_ino will be set to 0\n");
   }
   __wut_fsa_translate_stat(deviceData->clientHandle, &dir->entry_data.info, ino, filestat);

   if (snprintf(filename, NAME_MAX, "%s", dir->entry_data.name) >= NAME_MAX) {
      WUT_DEBUG_REPORT("__wut_fsa_dirnext: snprintf filename result was truncated\n");
   }

   return 0;
}
