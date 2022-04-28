#include "devoptab_fs.h"

int
__wut_fs_stat(struct _reent *r,
              const char *path,
              struct stat *st) {
   FSStatus status;
   FSCmdBlock cmd;
   FSStat fsStat;

   if (!path || !st) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   FSInitCmdBlock(&cmd);

   // First try open as file
   status = FSGetStat(__wut_devoptab_fs_client, &cmd, fixedPath, &fsStat, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      free(fixedPath);
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }
   free(fixedPath);

   memset(st, 0, sizeof(struct stat));

   st->st_nlink = 1;
   st->st_atime = __wut_fs_translate_time(fsStat.modified);
   st->st_ctime = __wut_fs_translate_time(fsStat.created);
   st->st_mtime = __wut_fs_translate_time(fsStat.modified);
   st->st_mode = __wut_translate_mode(fsStat);

   if (!(fsStat.flags & FS_STAT_DIRECTORY)) {
      st->st_size = fsStat.size;
      st->st_uid = fsStat.owner;
      st->st_gid = fsStat.group;
   }

   return 0;
}