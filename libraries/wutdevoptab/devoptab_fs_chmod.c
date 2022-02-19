#include <sys/stat.h>
#include "devoptab_fs.h"

int
__wut_fs_chmod(struct _reent *r,
               const char *path,
               mode_t mode)
{
   FSStatus status;
   FSCmdBlock cmd;

   if (!path) {
      r->_errno = EINVAL;
      return -1;
   }

   char *fixedPath = __wut_fs_fixpath(r, path);
   if (!fixedPath) {
      return -1;
   }

   FSMode translatedMode = 0;
   if (mode & S_IRUSR) {
      translatedMode |= FS_MODE_READ_OWNER;
   }
   if (mode & S_IWUSR) {
      translatedMode |= FS_MODE_WRITE_OWNER;
   }
   if (mode & S_IXUSR) {
      translatedMode |= FS_MODE_EXEC_OWNER;
   }

   if (mode & S_IRGRP) {
      translatedMode |= FS_MODE_READ_GROUP;
   }
   if (mode & S_IWGRP) {
      translatedMode |= FS_MODE_WRITE_GROUP;
   }
   if (mode & S_IXGRP) {
      translatedMode |= FS_MODE_EXEC_GROUP;
   }

   if (mode & S_IROTH) {
      translatedMode |= FS_MODE_READ_OTHER;
   }
   if (mode & S_IWOTH) {
      translatedMode |= FS_MODE_WRITE_OTHER;
   }
   if (mode & S_IXOTH) {
      translatedMode |= FS_MODE_EXEC_OTHER;
   }

   FSInitCmdBlock(&cmd);
   status = FSChangeMode(__wut_devoptab_fs_client, &cmd, fixedPath,
                         translatedMode, 0x777, FS_ERROR_FLAG_ALL);
   free(fixedPath);
   if (status < 0) {
      r->_errno = __wut_fs_translate_error(status);
      return -1;
   }

   return 0;
}
