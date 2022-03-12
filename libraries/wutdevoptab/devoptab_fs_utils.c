#include "devoptab_fs.h"

char *
__wut_fs_fixpath(struct _reent *r,
                 const char *path)
{
   char *p;
   char *fixedPath;

   if (!path) {
      r->_errno = EINVAL;
      return NULL;
   }

   p = strchr(path, ':') + 1;
   if (!strchr(path, ':')) {
      p = (char*)path;
   }

   if (strlen(p) > PATH_MAX) {
      r->_errno = ENAMETOOLONG;
      return NULL;
   }

   fixedPath = memalign(0x40, PATH_MAX + 1);
   if (!fixedPath) {
      r->_errno = ENOMEM;
      return NULL;
   }

   // cwd is handled by coreinit, so just strip the 'device:' if it exists
   strcpy(fixedPath, p);
   return fixedPath;
}

int
__wut_fs_translate_error(FSStatus error)
{
   switch ((int)error) {
   case FS_STATUS_END:
      return ENOENT;
   case FS_STATUS_CANCELLED:
      return ECANCELED;
   case FS_STATUS_EXISTS:
      return EEXIST;
   case FS_STATUS_MEDIA_ERROR:
      return EIO;
   case FS_STATUS_NOT_FOUND:
      return ENOENT;
   case FS_STATUS_PERMISSION_ERROR:
      return EPERM;
   case FS_STATUS_STORAGE_FULL:
      return ENOSPC;
   case FS_STATUS_FILE_TOO_BIG:
      return EFBIG;
   case FS_STATUS_NOT_DIR:
      return ENOTDIR;
   case FS_STATUS_NOT_FILE:
      return EISDIR;
   case FS_STATUS_MAX:
      return ENFILE;
   case FS_STATUS_ACCESS_ERROR:
      return EACCES;
   case FS_STATUS_JOURNAL_FULL:
      return ENOSPC;
   case FS_STATUS_UNSUPPORTED_CMD:
      return ENOTSUP;
   case FS_STATUS_MEDIA_NOT_READY:
      return EOWNERDEAD;
   case FS_STATUS_ALREADY_OPEN:
   case FS_STATUS_CORRUPTED:
   case FS_STATUS_FATAL_ERROR:
      return EIO;
   }
   return (int)error;
}
