#include "devoptab_fs.h"

int
__wut_fs_dirclose(struct _reent *r,
                  DIR_ITER *dirState)
{
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_dir_t *dir;

   if (!dirState) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   dir = (__wut_fs_dir_t *)(dirState->dirStruct);
   status = FSCloseDir(__wut_devoptab_fs_client, &cmd, dir->fd, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
