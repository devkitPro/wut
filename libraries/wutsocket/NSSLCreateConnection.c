#include "wut_socket.h"
#include <nsysnet/nssl.h>

NSSLConnectionHandle
RPLWRAP(NSSLCreateConnection)(NSSLContextHandle context,
                              const char *host,
                              int32_t hostLength,
                              int32_t options,
                              int32_t socket,
                              int32_t block);

NSSLConnectionHandle
NSSLCreateConnection(NSSLContextHandle context,
                     const char *host,
                     int32_t hostLength,
                     int32_t options,
                     int32_t socket,
                     int32_t block)
{
   socket = __wut_get_nsysnet_fd(socket);
   if (socket == -1) {
      return NSSL_ERROR_INVALID_FD;
   }

   return RPLWRAP(NSSLCreateConnection)(context,
                                        host,
                                        hostLength,
                                        options,
                                        socket,
                                        block);
}
