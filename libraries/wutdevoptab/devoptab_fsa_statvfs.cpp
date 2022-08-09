#include "devoptab_fsa.h"

int
__wut_fs_statvfs(struct _reent *r,
                 const char *path,
                 struct statvfs *buf)
{
   //TODO: FSGetFileSystemInfo
   r->_errno = ENOSYS;
   return -1;
}
