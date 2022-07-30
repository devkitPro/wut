#include "devoptab_fs.h"

// Extended "magic" value that allows opening files with FS_OPEN_FLAG_UNENCRYPTED in underlying FSOpenFileEx() call similar to O_DIRECTORY
#define O_UNENCRYPTED 0x4000000

int
__wut_fs_open(struct _reent *r,
              void *fileStruct,
              const char *path,
              int flags,
              int mode) {
   FSFileHandle fd;
   FSStatus status;
   FSCmdBlock cmd;
   const char *fsMode;
   __wut_fs_file_t *file;

   if (!fileStruct || !path) {
      r->_errno = EINVAL;
      return -1;
   }

   bool createFileIfNotFound = false;
   bool failIfFileNotFound = false;
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
   } else if (((flags & O_ACCMODE) == O_WRONLY) && ((flags & commonFlagMask) == (O_CREAT))) {
      // Cafe OS doesn't have a matching mode for this, so we have to be creative and create the file.
      createFileIfNotFound = true;
      // It's not possible to open a file with write only mode which doesn't truncate the file
      // Technically we could read from the file, but our read implementation is blocking this.
      fsMode = "r+";
   } else if (((flags & O_ACCMODE) == O_WRONLY) && ((flags & commonFlagMask) == (O_APPEND))) {
      // Cafe OS doesn't have a matching mode for this, so we have to check if the file exists.
      failIfFileNotFound = true;
      fsMode = "a";
   } else if (((flags & O_ACCMODE) == O_WRONLY) && ((flags & commonFlagMask) == (O_TRUNC))) {
      // As above
      failIfFileNotFound = true;
      fsMode = "w";
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
   FSOpenFileFlags openFlags = (flags & O_UNENCRYPTED) ? FS_OPEN_FLAG_UNENCRYPTED : FS_OPEN_FLAG_NONE;
   uint32_t preallocSize = 0;

   if (createFileIfNotFound || failIfFileNotFound || (flags & (O_EXCL | O_CREAT)) == (O_EXCL | O_CREAT)) {
      // Check if file exists
      FSStat stat;
      status = FSGetStat(__wut_devoptab_fs_client, &cmd, fixedPath, &stat, FS_ERROR_FLAG_ALL);
      if (status == FS_STATUS_NOT_FOUND) {
         if (createFileIfNotFound) { // Create new file if needed
            status = FSOpenFileEx(__wut_devoptab_fs_client, &cmd, fixedPath, "w", __wut_fs_translate_permission_mode(mode),
                                  openFlags, preallocSize, &fd, FS_ERROR_FLAG_ALL);
            if (status == FS_STATUS_OK) {
               FSCloseFile(__wut_devoptab_fs_client, &cmd, fd, FS_ERROR_FLAG_ALL);
               fd = -1;
            } else {
               free(fixedPath);
               r->_errno = __wut_fs_translate_error(status);
               return -1;
            }
         } else if (failIfFileNotFound) { // Return an error if we don't we create new files
            r->_errno = __wut_fs_translate_error(status);
            return -1;
         }
      } else if (status == FS_STATUS_OK) {
         // If O_CREAT and O_EXCL are set, open() shall fail if the file exists.
         if ((flags & (O_EXCL | O_CREAT)) == (O_EXCL | O_CREAT)) {
            r->_errno = EEXIST;
            return -1;
         }
      }
   }

   status = FSOpenFileEx(__wut_devoptab_fs_client, &cmd, fixedPath, fsMode, __wut_fs_translate_permission_mode(mode),
                         openFlags, preallocSize, &fd, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   file = (__wut_fs_file_t *) fileStruct;
   file->fd = fd;
   file->flags = (flags & (O_ACCMODE | O_APPEND | O_SYNC));
   // Is always 0, even if O_APPEND is set.
   file->offset = 0;
   if (flags & O_APPEND) {
      FSStat stat;
      status = FSGetStatFile(__wut_devoptab_fs_client, &cmd, fd, &stat, FS_ERROR_FLAG_ALL);
      if (status < 0) {
         FSCloseFile(__wut_devoptab_fs_client, &cmd, fd, FS_ERROR_FLAG_ALL);
         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }
      file->appendOffset = stat.size;
   }

   return 0;
}
