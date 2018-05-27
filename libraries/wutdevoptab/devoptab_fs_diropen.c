#include "devoptab_fs.h"

DIR_ITER *
__wut_fs_diropen(struct _reent *r,
                 DIR_ITER *dirState,
                 const char *path)
{
   FSDirectoryHandle fd;
   FSStatus rc;

   if (path == NULL) {
      return NULL;
   }

   char *path_fixed = __wut_fs_fixpath(r,path);

   if (!path_fixed) {
      r->_errno = ENOMEM;
      return NULL;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   __wut_fs_dir_t *dir = (__wut_fs_dir_t *)(dirState->dirStruct);
   rc = FSOpenDir(__wut_devoptab_fs_client, &fsCmd, path_fixed, &fd, -1);

   if (rc >= 0) {
      dir->magic = FS_DIRITER_MAGIC;
      dir->fd    = fd;
      memset(&dir->entry_data, 0, sizeof(dir->entry_data));
      free(path_fixed);
      return dirState;
   }

   free(path_fixed);
   r->_errno = __wut_fs_translate_error(rc);
   return NULL;
}
