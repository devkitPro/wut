#include "wut_socket.h"

int
getsockname(int sockfd,
            struct sockaddr *addr,
            socklen_t *addrlen)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if(sockfd == -1) {
      return -1;
   }
   rc = NSYSNET_C(getsockname)(sockfd, addr, addrlen);
   return __wut_get_nsysnet_result(NULL, rc);
}

