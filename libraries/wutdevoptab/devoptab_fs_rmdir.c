#include "devoptab_fs.h"

int
__wut_fs_rmdir(struct _reent *r,
               const char *name)
{
   FSStatus status;
   FSCmdBlock cmd;

   if (!name) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, name);
   if (!fixedPath) {
      return -1;
   }

   FSInitCmdBlock(&cmd);
   status = FSRemove(__wut_devoptab_fs_client, &cmd, fixedPath, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
