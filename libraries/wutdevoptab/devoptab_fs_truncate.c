#include "devoptab_fs.h"

int
__wut_fs_ftruncate(struct _reent *r,
                   void *fd,
                   off_t len)
{
   FSStatus rc;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Make sure length is non-negative
   if (len < 0) {
      r->_errno = EINVAL;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   // Set the new file size
   rc = FSSetPosFile(__wut_devoptab_fs_client, &fsCmd, file->fd, len, -1);

   if (rc >= 0) {
      return 0;
   }

   rc = FSTruncateFile(__wut_devoptab_fs_client, &fsCmd, file->fd, -1);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
