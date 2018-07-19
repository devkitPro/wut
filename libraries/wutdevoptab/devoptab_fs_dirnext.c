#include "devoptab_fs.h"

int
__wut_fs_dirnext(struct _reent *r,
                 DIR_ITER *dirState,
                 char *filename,
                 struct stat *filestat)
{
   FSStatus rc;
   __wut_fs_dir_t *dir = (__wut_fs_dir_t *)(dirState->dirStruct);

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   // Fetch the next dir
   memset(&dir->entry_data, 0, sizeof(dir->entry_data));
   rc = FSReadDir(__wut_devoptab_fs_client, &fsCmd, dir->fd, &dir->entry_data, -1);

   if (rc < 0) {
      // There are no more entries; ENOENT signals end-of-directory
      r->_errno = ENOENT;
      return -1;
   }

   if (rc >= 0) {
      memset(filestat, 0, sizeof(struct stat));

      // Fill in the stat info
      filestat->st_ino = 0;

      if (dir->entry_data.info.flags & FS_STAT_DIRECTORY) {
         filestat->st_mode = S_IFDIR;
      } else {
         filestat->st_mode = S_IFREG;
      }

      filestat->st_uid = dir->entry_data.info.owner;
      filestat->st_gid = dir->entry_data.info.group;
      filestat->st_size = dir->entry_data.info.size;

      memset(filename, 0, NAME_MAX);
      strcpy(filename, dir->entry_data.name);
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
