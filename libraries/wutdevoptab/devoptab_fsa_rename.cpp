#include "devoptab_fsa.h"

int
__wut_fsa_rename(struct _reent *r,
                 const char *oldName,
                 const char *newName) {
   FSError status;
   char *fixedOldPath, *fixedNewPath;
   __wut_fsa_device_t *deviceData;

   if (!oldName || !newName) {
      r->_errno = EINVAL;
      return -1;
   }

   fixedOldPath = __wut_fsa_fixpath(r, oldName);
   if (!fixedOldPath) {
      r->_errno = ENOMEM;
      return -1;
   }

   fixedNewPath = __wut_fsa_fixpath(r, newName);
   if (!fixedNewPath) {
      free(fixedOldPath);
      r->_errno = ENOMEM;
      return -1;
   }

   deviceData = (__wut_fsa_device_t *) r->deviceData;

   status = FSARename(deviceData->clientHandle, fixedOldPath, fixedNewPath);
   if (status < 0) {
      WUT_DEBUG_REPORT("FSARename(0x%08X, %s, %s) failed: %s\n",
                       deviceData->clientHandle, fixedOldPath, fixedNewPath, FSAGetStatusStr(status));
      free(fixedOldPath);
      free(fixedNewPath);
      r->_errno = __wut_fsa_translate_error(status);
      return -1;
   }
   free(fixedOldPath);
   free(fixedNewPath);

   return 0;
}
