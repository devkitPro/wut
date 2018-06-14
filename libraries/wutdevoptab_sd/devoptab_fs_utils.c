#include "devoptab_sd.h"

char *
__wut_fs_fixpath(struct _reent *r,
                 const char *path)
{
   char *p = strchr(path, ':') + 1;

   if (!strchr(path, ':')) {
      p = (char*)path;
   }

   if (strlen(p) > PATH_MAX) {
      r->_errno = ENAMETOOLONG;
      return NULL;
   }

   char *__fixedpath = memalign(0x40, PATH_MAX + 1);

   if (__fixedpath == NULL) {
      return NULL;
   }

   // cwd is handled by coreinit, so just strip the 'device:' if it exists
   strcpy(__fixedpath, p);
   return __fixedpath;
}

int
__wut_fs_translate_error(FSStatus error)
{
   switch (error) {
   case FS_STATUS_CANCELLED:
      return EINVAL;
   case FS_STATUS_EXISTS:
      return EEXIST;
   case FS_STATUS_NOT_FOUND:
      return ENOENT;
   case FS_STATUS_STORAGE_FULL:
      return ENOSPC;
   case FS_ERROR_INVALID_PATH:
      return ENAMETOOLONG;
   default:
      return (int)error;
   }
}

