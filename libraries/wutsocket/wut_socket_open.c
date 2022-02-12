#include "wut_socket.h"

int __wut_socket_open(struct _reent *r,
                      void *fileStruct,
                      const char *path,
                      int flags,
                      int mode)
{
   r->_errno = ENOSYS;
   return -1;
}
