#include "devoptab_fs.h"

off_t
__wut_fs_seek(struct _reent *r,
              void *fd,
              off_t pos,
              int whence)
{
   FSStatus status;
   FSCmdBlock cmd;
   FSStat fsStat;
   uint64_t offset;
   __wut_fs_file_t *file;

   if (!fd) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file = (__wut_fs_file_t *)fd;

   // Find the offset to see from
   switch(whence) {
   // Set absolute position; start offset is 0
   case SEEK_SET:
      offset = 0;
      break;

   // Set position relative to the current position
   case SEEK_CUR:
      offset = file->offset;
      break;

   // Set position relative to the end of the file
   case SEEK_END: {
      status = FSGetStatFile(__wut_devoptab_fs_client, &cmd, file->fd, &fsStat,
                             FS_ERROR_FLAG_ALL);
      if (status < 0) {
         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }
      offset = fsStat.size;
      break;
   }
   // An invalid option was provided
   default:
      r->_errno = EINVAL;
      return -1;
   }

   if(pos < 0 && offset < -pos) {
      // Don't allow seek to before the beginning of the file
      r->_errno = EINVAL;
      return -1;
   } else if (offset + pos > UINT32_MAX) {
      // Check for overflow
      r->_errno = EINVAL;
      return -1;
   }

   uint32_t old_offset = file->offset;
   file->offset = offset + pos;

   status = FSSetPosFile(__wut_devoptab_fs_client, &cmd, file->fd, file->offset,
                         FS_ERROR_FLAG_ALL);
   if (status < 0) {
      // revert offset update on error.
      file->offset = old_offset;
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return file->offset;
}
