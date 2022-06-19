#include "devoptab_fs.h"

int
__wut_fs_fstat(struct _reent *r,
               void *fd,
               struct stat *st)
{
   FSStatus status;
   FSStat fsStat;
   FSCmdBlock cmd;
   __wut_fs_file_t *file;

   if (!fd || !st) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file = (__wut_fs_file_t *)fd;
   status = FSGetStatFile(__wut_devoptab_fs_client, &cmd, file->fd, &fsStat,
                          FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   __wut_fs_translate_stat(&fsStat, st);

   return 0;
}
