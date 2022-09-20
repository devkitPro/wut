#include "devoptab_fs.h"

#include <sys/param.h>

ssize_t __wut_fs_read(struct _reent *r, void *fd, char *ptr, size_t len) {
   if (!fd || !ptr) {
      r->_errno = EINVAL;
      return -1;
   }

   // Check that the file was opened with read access
   __wut_fs_file_t *file = (__wut_fs_file_t *) fd;
   if ((file->flags & O_ACCMODE) == O_WRONLY) {
      r->_errno = EBADF;
      return -1;
   }

   // cache-aligned, cache-line-sized
   __attribute__((aligned(0x40))) uint8_t alignedBuffer[0x40];

   FSCmdBlock cmd;
   FSInitCmdBlock(&cmd);

   size_t bytesRead = 0;
   while (bytesRead < len) {
      // only use input buffer if cache-aligned and read size is a multiple of cache line size
      // otherwise read into alignedBuffer
      uint8_t *tmp = (uint8_t *) ptr;
      size_t size = len - bytesRead;

      if (size < 0x40) {
         // read partial cache-line back-end
         tmp = alignedBuffer;
      } else if ((uintptr_t) ptr & 0x3F) {
         // read partial cache-line front-end
         tmp = alignedBuffer;
         size = MIN(size, 0x40 - ((uintptr_t) ptr & 0x3F));
      } else {
         // read whole cache lines
         size &= ~0x3F;
      }

      FSStatus status = FSReadFile(__wut_devoptab_fs_client, &cmd, tmp, 1, size,
                                   file->fd, 0, FS_ERROR_FLAG_ALL);

      if (status < 0) {
         if (bytesRead != 0) {
            return bytesRead; // error after partial read
         }

         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }

      if (tmp == alignedBuffer) {
         memcpy(ptr, alignedBuffer, status);
      }

      file->offset += status;
      bytesRead += status;
      ptr += status;

      if (status != size) {
         return bytesRead; // partial read
      }
   }

   return bytesRead;
}