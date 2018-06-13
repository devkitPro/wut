#include "devoptab_sd.h"

int
__wut_fs_rmdir(struct _reent *r,
               const char *name)
{
   FSStatus  rc;

   if (name == NULL) {
      return -1;
   }

   char *path_fix = __wut_fs_fixpath(r, name);

   if (!path_fix) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSRemove(__wut_devoptab_sd_client, &fsCmd, path_fix, -1);
   free(path_fix);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
