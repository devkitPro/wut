#include "wut_socket.h"
#include <netdb.h>

struct servent *
getservbyname(const char *name,
              const char *proto)
{
   h_errno = NO_RECOVERY;
   errno   = ENOSYS;
   return NULL;
}

struct servent *
getservbyport(int port,
              const char *proto)
{
   h_errno = NO_RECOVERY;
   errno   = ENOSYS;
   return NULL;
}

struct servent *
getservent(void)
{
   h_errno = NO_RECOVERY;
   errno   = ENOSYS;
   return NULL;
}

struct hostent *
gethostent(void)
{
   h_errno = NO_RECOVERY;
   errno   = ENOSYS;
   return NULL;
}
