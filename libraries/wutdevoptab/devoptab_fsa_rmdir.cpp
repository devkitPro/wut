#include "devoptab_fsa.h"

int
__wut_fsa_rmdir(struct _reent *r,
                const char *name) {
   FSError status;
   __wut_fsa_device_t *deviceData;

   if (!name) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fsa_fixpath(r, name);
   if (!fixedPath) {
      r->_errno = ENOMEM;
      return -1;
   }

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   status = FSARemove(deviceData->clientHandle, fixedPath);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSARemove(0x%08X, %s) failed: %s\n",
                       deviceData->clientHandle, fixedPath, FSAGetStatusStr(status));
      free(fixedPath);
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }

   free(fixedPath);

   return 0;
}
