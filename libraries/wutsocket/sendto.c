#include "wut_socket.h"

ssize_t
sendto(int sockfd,
       const void *buf,
       size_t len,
       int flags,
       const struct sockaddr *dest_addr,
       socklen_t addrlen)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if (sockfd == -1) {
      return -1;
   }
   rc = NSYSNET_C(sendto)(sockfd, buf, len, flags, dest_addr, addrlen);
   return (ssize_t)__wut_get_nsysnet_result(NULL, rc);
}

