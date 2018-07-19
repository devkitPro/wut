#include "devoptab_fs.h"

ssize_t
__wut_fs_read(struct _reent *r,
              void *fd,
              char *ptr,
              size_t len)
{
   FSStatus rc;
   uint32_t bytes, bytesRead = 0;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Check that the file was opened with read access
   if ((file->flags & O_ACCMODE) == O_WRONLY) {
      r->_errno = EBADF;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   FSStat fsstat;
   rc = FSGetStatFile(__wut_devoptab_fs_client, &fsCmd, file->fd, &fsstat, -1);

   if(rc < 0) {
      r->_errno = __wut_fs_translate_error(rc);
      return -1;
   }

   // Copy to internal buffer and read in chunks.
   uint8_t *tmp_buffer = memalign(0x40, 8192);

   while(len > 0) {
      size_t toRead = len;

      if (toRead > 8192) {
         toRead = 8192;
      }

      // Write the data
      rc = FSReadFile(__wut_devoptab_fs_client, &fsCmd, tmp_buffer, 1, toRead, file->fd, 0, -1);

      if(rc <= 0)
      {
         free(tmp_buffer);

         // Return partial transfer
         if (bytesRead > 0) {
            return bytesRead;
         }

         r->_errno = __wut_fs_translate_error(rc);
         return -1;
      } else {
         bytes = rc;
      }

      // Copy to internal buffer
      memcpy(ptr, tmp_buffer, bytes);

      file->offset += bytes;
      bytesRead    += bytes;
      ptr          += bytes;
      len          -= bytes;
   }

   free(tmp_buffer);
   return bytesRead;
}
