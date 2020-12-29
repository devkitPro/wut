#include "devoptab_fs.h"

int
__wut_fs_rename(struct _reent *r,
                const char *oldName,
                const char *newName)
{
   FSStatus status;
   FSCmdBlock cmd;
   char *fixedOldPath, *fixedNewPath;

   if (!oldName || !newName) {
      r->_errno = EINVAL;
      return -1;
   }

   fixedOldPath = __wut_fs_fixpath(r, oldName);
   if (!fixedOldPath) {
      return -1;
   }

   fixedNewPath = __wut_fs_fixpath(r, newName);
   if (!fixedNewPath) {
      free(fixedOldPath);
      return -1;
   }

   FSInitCmdBlock(&cmd);
   status = FSRename(__wut_devoptab_fs_client, &cmd, fixedOldPath, fixedNewPath,
                     FS_ERROR_FLAG_ALL);
   free(fixedOldPath);
   free(fixedNewPath);

   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
