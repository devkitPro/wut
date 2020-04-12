#include "wut_socket.h"

int
setsockopt(int sockfd,
           int level,
           int optname,
           const void *optval,
           socklen_t optlen)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if(sockfd == -1) {
      return -1;
   }
   rc = NSYSNET_C(setsockopt)(sockfd, level, optname, optval, optlen);
   return __wut_get_nsysnet_result(NULL, rc);
}

