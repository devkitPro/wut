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
      p = (char *) path;
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

int __wut_fs_translate_error(FSStatus error)
{
   switch ((int32_t) error) {
      case FS_STATUS_END:
         return ENOENT;
      case FS_STATUS_CANCELLED:
         return EINVAL;
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
      case FS_ERROR_ALREADY_EXISTS:
         return EEXIST;
      case FS_ERROR_BUSY:
         return EBUSY;
      case FS_ERROR_CANCELLED:
         return ECANCELED;
      case FS_STATUS_FILE_TOO_BIG:
         return EFBIG;
      case FS_ERROR_INVALID_PATH:
         return ENAMETOOLONG;
      case FS_ERROR_NOT_DIR:
         return ENOTDIR;
      case FS_ERROR_NOT_FILE:
         return EISDIR;
      case FS_ERROR_OUT_OF_RANGE:
         return ESPIPE;
      case FS_ERROR_UNSUPPORTED_COMMAND:
         return ENOTSUP;
      case FS_ERROR_WRITE_PROTECTED:
         return EROFS;
      default:
         return (int) error;
   }
}
