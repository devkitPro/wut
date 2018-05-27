#include "devoptab_fs.h"

int
__wut_fs_mkdir(struct _reent *r,
               const char *path,
               int mode)
{
   FSError  rc;

   if (path == NULL) {
      return -1;
   }

   char *path_fix = __wut_fs_fixpath(r, path);

   if (!path_fix) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   // TODO: Use mode to set directory attributes.
   rc = FSMakeDir(__wut_devoptab_fs_client, &fsCmd, path_fix, -1);
   free(path_fix);

   if (rc == FS_ERROR_ALREADY_EXISTS) {
      r->_errno = EEXIST;
      return -1;
   } else if(rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
