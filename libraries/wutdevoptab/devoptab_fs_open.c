#include "devoptab_fs.h"

// Extended "magic" value that allows opening files with FS_OPEN_FLAG_UNENCRYPTED in underlying FSOpenFileEx() call similar to O_DIRECTORY
#define O_UNENCRYPTED 0x4000000

int
__wut_fs_open(struct _reent *r,
              void *fileStruct,
              const char *path,
              int flags,
              int mode)
{
   FSFileHandle fd;
   FSStatus status;
   FSCmdBlock cmd;
   const char *fsMode;
   __wut_fs_file_t *file;

   if (!fileStruct || !path) {
      r->_errno = EINVAL;
      return -1;
   }

   // Map flags to open modes
   int commonFlagMask = O_CREAT | O_TRUNC | O_APPEND;
   if (((flags & O_ACCMODE) == O_RDONLY) && !(flags & commonFlagMask)) {
      fsMode = "r";
   } else if (((flags & O_ACCMODE) == O_RDWR) && !(flags & commonFlagMask)) {
      fsMode = "r+";
   } else if (((flags & O_ACCMODE) == O_WRONLY) && ((flags & commonFlagMask) == (O_CREAT | O_TRUNC))) {
      fsMode = "w";
   } else if (((flags & O_ACCMODE) == O_RDWR) && ((flags & commonFlagMask) == (O_CREAT | O_TRUNC))) {
      fsMode = "w+";
   } else if (((flags & O_ACCMODE) == O_WRONLY) && ((flags & commonFlagMask) == (O_CREAT | O_APPEND))) {
      fsMode = "a";
   } else if (((flags & O_ACCMODE) == O_RDWR) && ((flags & commonFlagMask) == (O_CREAT | O_APPEND))) {
      fsMode = "a+";
   } else {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   // Open the file
   FSInitCmdBlock(&cmd);
   FSOpenFileFlags openFlags = (mode & O_UNENCRYPTED) ? FS_OPEN_FLAG_UNENCRYPTED : FS_OPEN_FLAG_NONE;
   uint32_t preallocSize = 0;
   status = FSOpenFileEx(__wut_devoptab_fs_client, &cmd, fixedPath, fsMode, __wut_fs_translate_permission_mode(mode), openFlags, preallocSize, &fd, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   file = (__wut_fs_file_t *)fileStruct;
   file->fd = fd;
   file->flags = (flags & (O_ACCMODE|O_APPEND|O_SYNC));
   file->offset = 0;
   if (flags & O_APPEND) {
      status = FSGetPosFile(__wut_devoptab_fs_client, &cmd, fd, &file->offset, FS_ERROR_FLAG_ALL);
      if (status < 0) {
         FSCloseFile(__wut_devoptab_fs_client, &cmd, fd, FS_ERROR_FLAG_ALL);
         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }
   }

   return 0;
}
