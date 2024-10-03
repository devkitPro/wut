#include "wut_socket.h"
#include <netdb.h>
#include <nsysnet/_netdb.h>

struct hostent *
gethostbyaddr(const void *addr,
              socklen_t len,
              int type)
{
   if (!addr || !len) {
      h_errno = HOST_NOT_FOUND;
      return NULL;
   }

   if (type != AF_INET) {
      h_errno = HOST_NOT_FOUND;
      return NULL;
   }

   struct hostent *ent = RPLWRAP(gethostbyaddr)(addr, len, type);

   h_errno             = *RPLWRAP(get_h_errno)();

   return ent;
}

struct hostent *
gethostbyname(const char *name)
{
   if (!name) {
      h_errno = HOST_NOT_FOUND;
      return NULL;
   }

   struct hostent *ent = RPLWRAP(gethostbyname)(name);

   h_errno             = *RPLWRAP(get_h_errno)();

   return ent;
}
