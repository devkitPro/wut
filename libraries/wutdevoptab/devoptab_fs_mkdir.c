#include "devoptab_fs.h"

int
__wut_fs_mkdir(struct _reent *r,
               const char *path,
               int mode)
{
   FSError status;
   FSCmdBlock cmd;
   char *fixedPath;

   if (!path) {
      r->_errno = EINVAL;
      return -1;
   }

   fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   // TODO: Use mode to set directory attributes.
   FSInitCmdBlock(&cmd);
   status = FSMakeDir(__wut_devoptab_fs_client, &cmd, fixedPath, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
