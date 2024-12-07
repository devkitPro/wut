#include "wut_socket.h"

ssize_t
__wut_socket_read(struct _reent *r,
                  void *fd,
                  char *ptr,
                  size_t len)
{
   int sockfd = *(int *)fd;
   int rc     = RPLWRAP(recv)(sockfd, ptr, len, 0);
   return (ssize_t)__wut_get_nsysnet_result(r, rc);
}
