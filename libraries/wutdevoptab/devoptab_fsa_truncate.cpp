#include "devoptab_fsa.h"
#include <mutex>

int
__wut_fsa_ftruncate(struct _reent *r,
                    void *fd,
                    off_t len) {
   FSError status;
   __wut_fsa_file_t *file;
   __wut_fsa_device_t *deviceData;

   // Make sure length is non-negative
   if (!fd || len < 0) {
      r->_errno = EINVAL;
      return -1;
   }

   file = (__wut_fsa_file_t *) fd;

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   std::scoped_lock lock(file->mutex);

   // Set the new file size
   status = FSASetPosFile(deviceData->clientHandle, file->fd, len);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSASetPosFile(0x%08X, 0x%08X, 0x%08X) failed: %s\n",
                       deviceData->clientHandle, file->fd, len, FSAGetStatusStr(status));
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   status = FSATruncateFile(deviceData->clientHandle, file->fd);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSATruncateFile(0x%08X, 0x%08X) failed: %s\n",
                       deviceData->clientHandle, file->fd, FSAGetStatusStr(status));
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   return 0;
}
