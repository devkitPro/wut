#include "wut_socket.h"

in_addr_t
inet_addr(const char *cp)
{
   struct in_addr addr = {
      .s_addr = INADDR_NONE,
   };
   inet_aton(cp, &addr);
   return addr.s_addr;
}
