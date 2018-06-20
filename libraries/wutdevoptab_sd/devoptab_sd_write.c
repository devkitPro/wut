#include "devoptab_sd.h"

ssize_t
__wut_fs_write(struct _reent *r,
               void *fd,
               const char *ptr,
               size_t len)
{
   FSStatus rc;
   uint32_t bytes, bytesWritten = 0;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Check that the file was opened with write access
   if ((file->flags & O_ACCMODE) == O_RDONLY) {
      r->_errno = EBADF;
      return -1;
   }

   // Copy to internal buffer and write in chunks.
   uint8_t *tmp_buffer = memalign(0x40, 8192);

   while(len > 0) {
      size_t toWrite = len;

      if (toWrite > 8192) {
         toWrite = 8192;
      }

      // Copy to internal buffer
      memcpy(tmp_buffer, ptr, toWrite);

      // Set up command block
      FSCmdBlock fsCmd;
      FSInitCmdBlock(&fsCmd);

      // Write the data
      rc = FSWriteFile(__wut_devoptab_sd_client, &fsCmd, tmp_buffer, 1, toWrite, file->fd, 0, -1);

      if (rc < 0) {
         free(tmp_buffer);

         // Return partial transfer
         if (bytesWritten > 0) {
            return bytesWritten;
         }

         r->_errno = __wut_fs_translate_error(rc);
         return -1;
      } else {
         bytes = rc;
      }

      file->offset += bytes;
      bytesWritten += bytes;
      ptr          += bytes;
      len          -= bytes;
   }

   free(tmp_buffer);
   return bytesWritten;
}
