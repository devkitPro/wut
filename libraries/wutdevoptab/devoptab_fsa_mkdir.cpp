#include "devoptab_fsa.h"

int
__wut_fsa_mkdir(struct _reent *r,
                const char *path,
                int mode) {
   FSError status;
   char *fixedPath;
   __wut_fsa_device_t *deviceData;

   if (!path) {
      r->_errno = EINVAL;
      return -1;
   }

   fixedPath = __wut_fsa_fixpath(r, path);
   if (!fixedPath) {
      r->_errno = ENOMEM;
      return -1;
   }

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   FSMode translatedMode = __wut_fsa_translate_permission_mode(mode);

   status = FSAMakeDir(deviceData->clientHandle, fixedPath, translatedMode);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSAMakeDir(0x%08X, %s, 0x%X) failed: %s\n",
                       deviceData->clientHandle, fixedPath, translatedMode, FSAGetStatusStr(status));
      free(fixedPath);
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }
   free(fixedPath);

   return 0;
}
