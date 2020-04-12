#include "wut_socket.h"

const char *
inet_ntop(int af,
          const void *src,
          char *dst,
          socklen_t size)
{
   const char *rc = NSYSNET_C(inet_ntop)(af, src, dst, size);
   if (!rc) {
      errno = EAFNOSUPPORT;
   }
   return rc;
}
