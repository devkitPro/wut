#include "devoptab_fsa.h"

int
__wut_fs_dirnext(struct _reent *r,
                 DIR_ITER *dirState,
                 char *filename,
                 struct stat *filestat)
{
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_dir_t *dir;

   if (!dirState || !filename || !filestat) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   dir = (__wut_fs_dir_t *)(dirState->dirStruct);
   memset(&dir->entry_data, 0, sizeof(dir->entry_data));
   status = FSReadDir(__wut_devoptab_fs_client, &cmd, dir->fd, &dir->entry_data,
                      FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   __wut_fs_translate_stat(&dir->entry_data.info, filestat);

   memset(filename, 0, NAME_MAX);
   strcpy(filename, dir->entry_data.name);
   return 0;
}
