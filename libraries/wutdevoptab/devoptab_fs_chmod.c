#include <sys/stat.h>
#include "devoptab_fs.h"

static inline FSMode
__wut_fs_convert_mode(mode_t mode)
{
   // Convert normal Unix octal permission bits into CafeOS hexadecimal permission bits
   return (FSMode) (((mode & S_IRWXU) << 2) | ((mode & S_IRWXG) << 1) | (mode & S_IRWXO));
}

int
__wut_fs_chmod(struct _reent *r,
               const char *path,
               mode_t mode)
{
   FSStatus status;
   FSCmdBlock cmd;

   if (!path) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   FSMode translatedMode = __wut_fs_convert_mode(mode);

   FSInitCmdBlock(&cmd);
   status = FSChangeMode(__wut_devoptab_fs_client, &cmd, fixedPath,
                         translatedMode, 0x777, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
