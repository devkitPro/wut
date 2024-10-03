#include "wut_socket.h"

int
shutdown(int sockfd,
         int how)
{
   int rc;
   sockfd = __wut_get_nsysnet_fd(sockfd);
   if (sockfd == -1) {
      return -1;
   }
   rc = RPLWRAP(shutdown)(sockfd, how);
   return __wut_get_nsysnet_result(NULL, rc);
}
