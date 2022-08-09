#include "devoptab_fsa.h"
#include <mutex>
#include <sys/stat.h>

int
__wut_fsa_chmod(struct _reent *r,
                const char *path,
                mode_t mode) {
   FSError status;
   __wut_fsa_device_t *deviceData;

   if (!path) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fsa_fixpath(r, path);
   if (!fixedPath) {
      r->_errno = ENOMEM;
      return -1;
   }

   FSMode translatedMode = __wut_fsa_translate_permission_mode(mode);

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   status = FSAChangeMode(deviceData->clientHandle, fixedPath, translatedMode);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSAChangeMode(0x%08X, %s, 0x%X) failed: %s\n",
                       deviceData->clientHandle, fixedPath, translatedMode, FSAGetStatusStr(status));
      free(fixedPath);
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }
   free(fixedPath);

   return 0;
}
