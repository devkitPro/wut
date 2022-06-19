#include "devoptab_fs.h"

int
__wut_fs_fchmod(struct _reent *r,
                void *fd,
                mode_t mode)
{
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   FSInitCmdBlock(&cmd);
   status = FSChangeMode(__wut_devoptab_fs_client, &cmd, file->path,
                         __wut_fs_translate_permission_mode(mode), __wut_fs_translate_permission_mode(ACCESSPERMS), FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
