#include "devoptab_fs.h"

ssize_t __wut_fs_read(struct _reent *r, void *fd, char *ptr, size_t len) {
   FSStatus status = 0;
   FSCmdBlock cmd;
   size_t bytesRead = 0;
   size_t partSize[3];

   __wut_fs_file_t *file = (__wut_fs_file_t *) fd;
   __attribute__((aligned(0x40))) uint8_t alignedBuffer[0x40];

   if (!fd || !ptr) {
      r->_errno = EINVAL;
      return -1;
   }

   FSInitCmdBlock(&cmd);

   // Check that the file was opened with read access
   if ((file->flags & O_ACCMODE) == O_WRONLY) {
      r->_errno = EBADF;
      return -1;
   }

   partSize[0] =  (0x40 - ((uintptr_t)ptr & 0x3f)) & 0x3f;
   if (partSize[0] > len) partSize[0] = len;
   partSize[1] = len - partSize[0];
   partSize[2] = partSize[1] & 0x3f;
   partSize[1] -= partSize[2];

   if (partSize[0] + partSize[2] <= 0x40 && partSize[1] == 0) {
      partSize[0] += partSize[2];
      partSize[2] = 0;
   }

   uint8_t *tmp;

   for (int part=0; part<3; part++) {

      if (!partSize[0]) continue;

      if (part == 1) {
         tmp = (uint8_t *)ptr;
      } else {
         tmp =  alignedBuffer;
      }

      status = FSReadFile(__wut_devoptab_fs_client, &cmd, tmp, 1, partSize[part], file->fd, 0, FS_ERROR_FLAG_ALL);
      if (status < 0) {
         r->_errno = __wut_fs_translate_error(status);
         return -1;
      }
  
      if (part != 1) memcpy(ptr, alignedBuffer, status);
  
      bytesRead += status;
      ptr += status;

      if (status != partSize[part]) return bytesRead;
   }

   return bytesRead;
}