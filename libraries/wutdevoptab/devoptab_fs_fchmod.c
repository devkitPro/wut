#include "devoptab_fs.h"

int
__wut_fs_fchmod(struct _reent *r,
                void *fd,
                mode_t mode)
{
   // TODO: FSChangeMode and FSStatFile?
   r->_errno = ENOSYS;
   return -1;
}
