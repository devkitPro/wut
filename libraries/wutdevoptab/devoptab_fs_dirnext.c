#include "devoptab_fs.h"

int __wut_fs_dirnext(struct _reent *r,
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
   dir = (__wut_fs_dir_t *) (dirState->dirStruct);
   memset(&dir->entry_data, 0, sizeof(dir->entry_data));
   status = FSReadDir(__wut_devoptab_fs_client, &cmd, dir->fd, &dir->entry_data,
                      FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   // Fill in the stat info
   memset(filestat, 0, sizeof(struct stat));
   filestat->st_ino = 0;

   if (dir->entry_data.info.flags & FS_STAT_DIRECTORY) {
      filestat->st_mode = S_IFDIR;
   } else {
      filestat->st_mode = S_IFREG;
   }

   filestat->st_uid  = dir->entry_data.info.owner;
   filestat->st_gid  = dir->entry_data.info.group;
   filestat->st_size = dir->entry_data.info.size;

   memset(filename, 0, NAME_MAX);
   strcpy(filename, dir->entry_data.name);
   return 0;
}
