#include "wut_socket.h"

int
inet_pton(int af,
          const char *src,
          void *dst)
{
   int rc = NSYSNET_C(inet_pton)(af, src, dst);
   if (rc < 0) {
      errno = EAFNOSUPPORT;
   }
   return rc;
}
