#include "devoptab_fsa.h"
#include <mutex>

int
__wut_fsa_fstat(struct _reent *r,
                void *fd,
                struct stat *st) {
   FSError status;
   FSAStat fsStat;
   __wut_fsa_file_t *file;
   __wut_fsa_device_t *deviceData;

   if (!fd || !st) {
      r->_errno = EINVAL;
      return -1;
   }

   file = (__wut_fsa_file_t *) fd;
   deviceData = (__wut_fsa_device_t *) r->deviceData;

   std::scoped_lock lock(file->mutex);

   status = FSAGetStatFile(deviceData->clientHandle, file->fd, &fsStat);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSAGetStatFile(0x%08X, 0x%08X, 0x%08X) (%s) failed: %s\n",
                       deviceData->clientHandle, file->fd, &fsStat, FSAGetStatusStr(status));
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   ino_t ino = __wut_fsa_hashstring(file->fullPath);
   __wut_fsa_translate_stat(deviceData->clientHandle, &fsStat, ino, st);

   return 0;
}
