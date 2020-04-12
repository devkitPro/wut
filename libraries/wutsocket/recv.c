#include "wut_socket.h"

ssize_t
recv(int sockfd,
     void *buf,
     size_t len,
     int flags)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if(sockfd == -1) {
      return -1;
   }
   rc = NSYSNET_C(recv)(sockfd, buf, len, flags);
   return (ssize_t)__wut_get_nsysnet_result(NULL, rc);
}

