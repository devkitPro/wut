#include "devoptab_fs.h"

ssize_t
__wut_fs_read(struct _reent *r,
              void *fd,
              char *ptr,
              size_t len)
{
   FSStatus status = 0;
   FSCmdBlock cmd;
   uint8_t *alignedReadBuffer;
   uint32_t bytes, bytesRead;
   __wut_fs_file_t *file;

   if (!fd || !ptr) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);
   file = (__wut_fs_file_t *)fd;
   bytesRead = 0;

   // Check that the file was opened with read access
   if ((file->flags & O_ACCMODE) == O_WRONLY) {
      r->_errno = EBADF;
      return -1;
   }

   if((((uintptr_t) ptr) & 0x3F) == 0){
      status = FSReadFile(__wut_devoptab_fs_client, &cmd, (uint8_t *) ptr, 1,
                            len, file->fd, 0, -1);    
      if(status > 0){
         bytesRead = (uint32_t) status;
         file->offset += bytesRead;
      }
   } else {
      // Copy to internal buffer due to alignment requirement and read in chunks.
      // Using a buffer smaller than 128KiB takes a performance hit.
      int buffer_size = len < 128*1024 ? len : 128*1024;
      alignedReadBuffer = memalign(0x40, buffer_size);
      if(!alignedReadBuffer){
         r->_errno = ENOMEM;
         return -1;
      }
      while (len > 0) {
        size_t toRead = len > buffer_size ? buffer_size : len;

        // Write the data
        status = FSReadFile(__wut_devoptab_fs_client, &cmd, alignedReadBuffer, 1,
                            toRead, file->fd, 0, -1);
        if (status <= 0) {
           break;
        }

        // Copy to internal buffer
        bytes = (uint32_t)status;
        memcpy(ptr, alignedReadBuffer, bytes);

        file->offset += bytes;
        bytesRead    += bytes;
        ptr          += bytes;
        len          -= bytes;

        if (bytes < toRead) {
           // If we did not read the full requested toRead bytes then we reached
           // the end of the file.
           break;
        }
      }
      free(alignedReadBuffer);
   }

   // Return partial read
   if (bytesRead > 0) {
      return bytesRead;
   }

   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
