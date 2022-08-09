#include "devoptab_fsa.h"

ssize_t __wut_fs_write(struct _reent *r, void *fd, const char *ptr, size_t len) {
   if (!fd || !ptr) {
      r->_errno = EINVAL;
      return -1;
   }

   // Check that the file was opened with write access
   __wut_fs_file_t *file = (__wut_fs_file_t *) fd;
   if ((file->flags & O_ACCMODE) == O_RDONLY) {
      r->_errno = EBADF;
      return -1;
   }

   // cache-aligned, cache-line-sized
   __attribute__((aligned(0x40))) uint8_t alignedBuffer[0x40];

   FSCmdBlock cmd;
   FSInitCmdBlock(&cmd);

   // If O_APPEND is set, we always write to the end of the file.
   // When writing we file->offset to the file size to keep in sync.
   if(file->flags & O_APPEND) {
      file->offset = file->appendOffset;
   }

   size_t bytesWritten = 0;
   while (bytesWritten < len) {
      // only use input buffer if cache-aligned and write size is a multiple of cache line size
      // otherwise write from alignedBuffer
      uint8_t *tmp = (uint8_t *) ptr;
      size_t size = len - bytesWritten;

      if (size < 0x40) {
         // write partial cache-line back-end
         tmp = alignedBuffer;
      } else if ((uintptr_t) ptr & 0x3F) {
         // write partial cache-line front-end
         tmp = alignedBuffer;
         size = MIN(size, 0x40 - ((uintptr_t) ptr & 0x3F));
      } else {
         // write whole cache lines
         size &= ~0x3F;
      }

      if (tmp == alignedBuffer) {
         memcpy(tmp, ptr, size);
      }

      FSStatus status = FSWriteFile(__wut_devoptab_fs_client, &cmd, tmp, 1, size,
                                    file->fd, 0, FS_ERROR_FLAG_ALL);
      if (status < 0) {
         if (bytesWritten != 0) {
            return bytesWritten; // error after partial write
         }

         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }

      file->appendOffset += status;
      file->offset += status;
      bytesWritten += status;
      ptr += status;

      if (status != size) {
         return bytesWritten; // partial write
      }
   }

   return bytesWritten;
}
