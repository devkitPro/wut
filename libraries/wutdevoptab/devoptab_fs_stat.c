#include "devoptab_fs.h"

int
__wut_fs_stat(struct _reent *r,
              const char *file,
              struct stat *st)
{
   int      fd;
   FSStatus rc;

   if (file == NULL) {
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   // First try open as file
   rc = FSOpenFile(__wut_devoptab_fs_client, &fsCmd, file, "r", (FSFileHandle*)&fd, -1);

   if (rc >= 0) {
      __wut_fs_file_t tmpfd = { .fd = fd };
      rc = __wut_fs_fstat(r, &tmpfd, st);
      FSCloseFile(__wut_devoptab_fs_client, &fsCmd, fd, -1);
      return rc;
   }

   // File failed, so lets try open as directory
   rc = FSOpenDir(__wut_devoptab_fs_client, &fsCmd, file, (FSDirectoryHandle*)&fd, -1);

   if (rc >= 0) {
      memset(st, 0, sizeof(struct stat));
      st->st_nlink = 1;
      st->st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO;
      FSCloseDir(__wut_devoptab_fs_client, &fsCmd, fd, -1);
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
