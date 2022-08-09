#include "devoptab_fsa.h"
#include <mutex>

int
__wut_fsa_close(struct _reent *r,
                void *fd) {
   FSError status;
   __wut_fsa_file_t *file;
   __wut_fsa_device_t *deviceData;

   if (!fd) {
      r->_errno = EINVAL;
      return -1;
   }

   file = (__wut_fsa_file_t *) fd;

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   std::scoped_lock lock(file->mutex);

   status = FSACloseFile(deviceData->clientHandle, file->fd);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSACloseFile(0x%08X, 0x%08X) (%s) failed: %s\n",
                       deviceData->clientHandle, file->fd, file->fullPath, FSAGetStatusStr(status));
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   return 0;
}
