#include "wut_socket.h"

int
bind(int sockfd,
     const struct sockaddr *addr,
     socklen_t addrlen)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if (sockfd == -1) {
      return -1;
   }
   rc = RPLWRAP(bind)(sockfd, addr, addrlen);
   return __wut_get_nsysnet_result(NULL, rc);
}
