#include "wut_socket.h"

int
socket(int domain,
       int type,
       int protocol)
{
   int rc, fd, dev;

   dev = FindDevice("soc:");
   if (dev == -1) {
      return -1;
   }

   fd = __alloc_handle(dev);
   if (fd == -1) {
      return -1;
   }

   rc = RPLWRAP(socket)(domain, type, protocol);
   if (rc == -1) {
      __release_handle(fd);
      return __wut_get_nsysnet_result(NULL, rc);
   }
   
   *(int *)__get_handle(fd)->fileStruct = rc;
   return fd;
}

