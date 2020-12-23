#include "devoptab_fs.h"

ssize_t
__wut_fs_write(struct _reent *r,
               void *fd,
               const char *ptr,
               size_t len)
{
   FSStatus status = 0;
   FSCmdBlock cmd;
   uint8_t *alignedWriteBuffer;
   uint32_t bytes, bytesWritten;
   __wut_fs_file_t *file;

   if (!fd || !ptr) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file = (__wut_fs_file_t *)fd;
   bytesWritten = 0;

   // Check that the file was opened with write access
   if ((file->flags & O_ACCMODE) == O_RDONLY) {
      r->_errno = EBADF;
      return -1;
   }

   if((((uint32_t) ptr) & 0x3F) == 0){
      status = FSWriteFile(__wut_devoptab_fs_client, &cmd, (uint8_t *) ptr,
                           1, len, file->fd, 0, -1);  
      if(status > 0){
         bytesWritten = (uint32_t) status;
         file->offset += bytesWritten;
      }
   } else {       
      // Copy to internal buffer due to alignment requirement and write in chunks.
      alignedWriteBuffer = memalign(0x40, 8192);
      while (len > 0) {
         size_t toWrite = len > 8192 ? 8192 : len;

         // Copy to internal buffer
         memcpy(alignedWriteBuffer, ptr, toWrite);

         // Write the data
         status = FSWriteFile(__wut_devoptab_fs_client, &cmd, alignedWriteBuffer,
                              1, toWrite, file->fd, 0, -1);
         if (status <= 0) {
            break;
         }

         bytes = (uint32_t)status;
         file->offset += bytes;
         bytesWritten += bytes;
         ptr          += bytes;
         len          -= bytes;

         if (bytes < toWrite) {
            break;
         }
      }
      free(alignedWriteBuffer);
   }

   // Return partial write
   if (bytesWritten > 0) {
      return bytesWritten;
   }

   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
