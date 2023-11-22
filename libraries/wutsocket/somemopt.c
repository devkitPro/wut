#include "wut_socket.h"

#include <nn/nets2.h>

int
somemopt(SOMemOptRequest request,
         void *buffer,
         uint32_t size,
         SOMemOptFlags flags)
{
   int rc = RPLWRAP(somemopt)(request, buffer, size, flags);
   return __wut_get_nsysnet_result(NULL, rc);
}
