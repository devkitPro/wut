#include "wut_socket.h"

ssize_t
recvfrom(int sockfd,
         void *buf,
         size_t len,
         int flags,
         struct sockaddr *src_addr,
         socklen_t *addrlen)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if (sockfd == -1) {
      return -1;
   }
   rc = RPLWRAP(recvfrom)(sockfd, buf, len, flags, src_addr, addrlen);
   return (ssize_t)__wut_get_nsysnet_result(NULL, rc);
}

