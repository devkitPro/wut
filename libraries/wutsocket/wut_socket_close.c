#include "wut_socket.h"

int
__wut_socket_close(struct _reent *r,
                   void *fd)
{
   int sockfd = *(int *)fd;
   int rc = RPLWRAP(socketclose)(sockfd);
   return __wut_get_nsysnet_result(r, rc);
}

