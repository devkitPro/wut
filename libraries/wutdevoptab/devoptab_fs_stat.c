#include "devoptab_fs.h"

int
__wut_fs_stat(struct _reent *r,
              const char *path,
              struct stat *st) {
   FSStatus status;
   FSCmdBlock cmd;
   FSStat fsStat;

   if (!path || !st) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   FSInitCmdBlock(&cmd);

   status = FSGetStat(__wut_devoptab_fs_client, &cmd, fixedPath, &fsStat, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      free(fixedPath);
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }
   free(fixedPath);

   __wut_fs_translate_stat(&fsStat, st);

   return 0;
}