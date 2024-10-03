#include "wut_socket.h"
#include <netdb.h>
#include <nsysnet/_netdb.h>

int
getaddrinfo(const char *node,
            const char *service,
            const struct addrinfo *hints,
            struct addrinfo **res)
{
   int rc;

   if (!node && !service) {
      return EAI_NONAME;
   }

   if (!res) {
      errno = EINVAL;
      return EAI_SYSTEM;
   }

   rc = RPLWRAP(getaddrinfo)(node, service, hints, res);

   return rc;
}

void
freeaddrinfo(struct addrinfo *res)
{
   RPLWRAP(freeaddrinfo)(res);
}

int
getnameinfo(const struct sockaddr *addr,
            socklen_t addrlen,
            char *host,
            socklen_t hostlen,
            char *serv,
            socklen_t servlen,
            int flags)
{
   int rc;

   rc = RPLWRAP(getnameinfo)(addr, addrlen, host, hostlen, serv, servlen, flags);

   return rc;
}

const char *
gai_strerror(int ecode)
{
   return RPLWRAP(gai_strerror)(ecode);
}
