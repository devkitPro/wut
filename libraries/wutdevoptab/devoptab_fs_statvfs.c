#include "devoptab_fs.h"

int
__wut_fs_statvfs(struct _reent *r,
                 const char *path,
                 struct statvfs *buf)
{
   FSStatus status;
   FSCmdBlock cmd;
   uint64_t freeSpace;
   FSStat driveStat;
   memset(buf, 0, sizeof(struct statvfs));

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   FSInitCmdBlock(&cmd);

   status = FSGetFreeSpaceSize(__wut_devoptab_fs_client, &cmd, fixedPath, &freeSpace, FS_ERROR_FLAG_ALL);
   if (status < 0) {
      free(fixedPath);
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   status = FSGetStat(__wut_devoptab_fs_client, &cmd, fixedPath, &driveStat, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   // File system block size
   buf->f_bsize = 512;
   // Fundamental file system block size
   buf->f_frsize = 512;
   // Total number of blocks on file system in units of f_frsize
   buf->f_blocks = driveStat.quotaSize / buf->f_frsize;
   // Free blocks available for all and for non-privileged processes
   buf->f_bfree = buf->f_bavail = freeSpace / buf->f_frsize;
   // Number of inodes at this point in time
   buf->f_files = 0xFFFFFFFF;
   // Free inodes available for all and for non-privileged processes
   buf->f_ffree = 0xFFFFFFFF;
   // File system id
   buf->f_fsid = (unsigned long) __wut_devoptab_fs_client;
   // Bit mask of f_flag values.
   buf->f_flag = 0;
   // Maximum length of filenames
   buf->f_namemax = 255;

   return 0;
}
