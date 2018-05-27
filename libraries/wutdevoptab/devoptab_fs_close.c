#include "devoptab_fs.h"

int
__wut_fs_close(struct _reent *r,
               void *fd)
{
   FSStatus rc;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSCloseFile(__wut_devoptab_fs_client, &fsCmd, file->fd, -1);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
