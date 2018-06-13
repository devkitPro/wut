#include "devoptab_sd.h"

int
__wut_fs_open(struct _reent *r,
              void *fileStruct,
              const char *path,
              int flags,
              int mode)
{
   FSFileHandle fd;
   FSStatus rc;

   if (path == NULL) {
      return -1;
   }

   char *path_fixed = __wut_fs_fixpath(r,path);
   if (!path_fixed) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Get pointer to our data
   __wut_fs_file_t *file = (__wut_fs_file_t *)fileStruct;
   const char *fs_mode;

   // Map flags to open modes
   if (flags == 0) {
      fs_mode = "r";
   } else if (flags == 2) {
      fs_mode = "r+";
   } else if (flags == 0x601) {
      fs_mode = "w";
   } else if(flags == 0x602) {
      fs_mode = "w+";
   } else if(flags == 0x209) {
      fs_mode = "a";
   } else if(flags == 0x20A) {
      fs_mode = "a+";
   } else {
      free(path_fixed);
      r->_errno = EINVAL;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   // Open the file
   rc = FSOpenFile(__wut_devoptab_sd_client, &fsCmd, path_fixed, fs_mode, &fd, -1);

   if (rc >= 0) {
      file->fd = fd;
      file->flags = (flags & (O_ACCMODE|O_APPEND|O_SYNC));
      FSGetPosFile(__wut_devoptab_sd_client, &fsCmd, fd, &file->offset, -1);
      free(path_fixed);
      return 0;
   }

   free(path_fixed);
   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
