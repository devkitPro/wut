#include "devoptab_fs.h"

int
__wut_fs_fstat(struct _reent *r,
               void *fd,
               struct stat *st)
{
   FSStatus status;
   FSStat fsStat;
   FSCmdBlock cmd;
   __wut_fs_file_t *file;

   if (!fd || !st) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file = (__wut_fs_file_t *)fd;
   status = FSGetStatFile(__wut_devoptab_fs_client, &cmd, file->fd, &fsStat,
                          FS_ERROR_FLAG_ALL);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   memset(st, 0, sizeof(struct stat));
   st->st_size  = fsStat.size;
   st->st_uid   = fsStat.owner;
   st->st_gid   = fsStat.group;
   st->st_nlink = 1;
   st->st_mode  = __wut_translate_mode(fsStat);
   st->st_atime = __wut_fs_translate_time(fsStat.modified);
   st->st_ctime = __wut_fs_translate_time(fsStat.created);
   st->st_mtime = __wut_fs_translate_time(fsStat.modified);

   return 0;
}
