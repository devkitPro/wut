#include "devoptab_fs.h"

int
__wut_fs_chmod(struct _reent *r,
               const char *path,
               mode_t mode)
{
   FSStatus rc;
   char *path_fix = __wut_fs_fixpath(r, path);

   if (!path_fix) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSChangeMode(__wut_devoptab_fs_client, &fsCmd, path_fix, (FSMode)mode, -1);
   free(path_fix);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
