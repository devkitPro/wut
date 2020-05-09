#include "wut_socket.h"

int
accept(int sockfd,
       struct sockaddr *address,
       socklen_t *addrlen)
{
   int rc, fd, dev;

   fd = __wut_get_nsysnet_fd(sockfd);
   if (fd == -1) {
      return -1;
   }

   dev = __get_handle(sockfd)->device;
   sockfd = fd;

   fd = __alloc_handle(dev);
   if (fd == -1) {
      return -1;
   }

   rc = NSYSNET_C(accept)(sockfd, address, addrlen);
   if (rc == -1) {
      __release_handle(fd);
      return __wut_get_nsysnet_result(NULL, rc);
   }
   
   *(int *)__get_handle(fd)->fileStruct = rc;
   return fd;
}

