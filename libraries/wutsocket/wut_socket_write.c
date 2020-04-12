#include "wut_socket.h"

ssize_t
__wut_socket_write(struct _reent *r,
                   void *fd,
                   const char *ptr,
                   size_t len)
{
   int sockfd = *(int *)fd;
   int rc = NSYSNET_C(send)(sockfd, ptr, len, 0);
   return (ssize_t)__wut_get_nsysnet_result(r, rc);
}

