#include "wut_socket.h"

#include <nn/ac.h>

long
gethostid(void)
{
   long ip = -1;
   ACGetAssignedAddress((uint32_t*) &ip);
   return ip;
}

int
gethostname(char *name,
            size_t len)
{
   struct in_addr in;
   in.s_addr = gethostid();
   const char *hostname = inet_ntop(AF_INET, &in, name, len);
   return hostname ? 0 : -1;
}
