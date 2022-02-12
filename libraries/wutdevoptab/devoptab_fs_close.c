#include "devoptab_fs.h"

int __wut_fs_close(struct _reent *r,
                   void *fd)
{
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_file_t *file;

   if (!fd) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file   = (__wut_fs_file_t *) fd;
   status = FSCloseFile(__wut_devoptab_fs_client, &cmd, file->fd, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
