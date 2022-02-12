#include "devoptab_fs.h"

int __wut_fs_ftruncate(struct _reent *r,
                       void *fd,
                       off_t len)
{
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_file_t *file;

   // Make sure length is non-negative
   if (!fd || len < 0) {
      r->_errno = EINVAL;
      return -1;
   }

   // Set the new file size
   FSInitCmdBlock(&cmd);
   file   = (__wut_fs_file_t *) fd;
   status = FSSetPosFile(__wut_devoptab_fs_client, &cmd, file->fd, len, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   status = FSTruncateFile(__wut_devoptab_fs_client, &cmd, file->fd, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
