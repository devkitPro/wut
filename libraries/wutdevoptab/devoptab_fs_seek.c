#include "devoptab_fs.h"

off_t
__wut_fs_seek(struct _reent *r,
              void *fd,
              off_t pos,
              int whence)
{
   FSStatus rc;
   uint64_t offset;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   FSStat fsstat;
   rc = FSGetStatFile(__wut_devoptab_fs_client, &fsCmd, file->fd, &fsstat, -1);

   if (rc < 0) {
      r->_errno = __wut_fs_translate_error(rc);
      return -1;
   }

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
   case SEEK_END:
      offset = fsstat.size;
      break;

   // An invalid option was provided
   default:
      r->_errno = EINVAL;
      return -1;
   }

   // TODO: A better check that prevents overflow.
   if(pos < 0 && offset < -pos) {
      // Don't allow seek to before the beginning of the file
      r->_errno = EINVAL;
      return -1;
   }

   // Update the current offset
   file->offset = offset + pos;
   FSStatus result = FSSetPosFile(__wut_devoptab_fs_client, &fsCmd, file->fd, file->offset, -1);

   if (result < 0) {
      return result;
   }

   return file->offset;
}
