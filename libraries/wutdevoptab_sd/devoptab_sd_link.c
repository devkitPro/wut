#include "devoptab_sd.h"

int
__wut_fs_link(struct _reent *r,
              const char *existing,
              const char *newLink)
{
   r->_errno = ENOSYS;
   return -1;
}
