#include "devoptab_sd.h"

int
__wut_fs_statvfs(struct _reent *r,
                 const char *path,
                 struct statvfs *buf)
{
   FSStatus rc;
   bool writable = false;
   char *path_fix = __wut_fs_fixpath(r, path);

   if (!path_fix)  {
      r->_errno = ENOMEM;
      return -1;
   }

   //TODO: FSGetFileSystemInfo

   free(path_fix);
   r->_errno = ENOSYS;
   return -1;
}
