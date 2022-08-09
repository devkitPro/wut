#include "devoptab_fsa.h"

DIR_ITER *
__wut_fs_diropen(struct _reent *r,
                 DIR_ITER *dirState,
                 const char *path)
{
   FSDirectoryHandle fd;
   FSStatus status;
   FSCmdBlock cmd;
   __wut_fs_dir_t *dir;

   if (!dirState || !path) {
      r->_errno = EINVAL;
      return NULL;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return NULL;
   }

   FSInitCmdBlock(&cmd);
   dir = (__wut_fs_dir_t *)(dirState->dirStruct);
   status = FSOpenDir(__wut_devoptab_fs_client, &cmd, fixedPath, &fd, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return NULL;
   }

   dir->magic = FS_DIRITER_MAGIC;
   dir->fd    = fd;
   memset(&dir->entry_data, 0, sizeof(dir->entry_data));
   return dirState;
}
