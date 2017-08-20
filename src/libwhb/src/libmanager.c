#include <nsysnet/socket.h>

/**
 * Socket Library (nsysnet.rpl)
 */

static BOOL
isSocketInitialized = FALSE;

static unsigned int
numberOfSocketClients = 0;

void
WHBInitializeSocketLibrary()
{
   if(!isSocketInitialized) {
      isSocketInitialized = TRUE;
      socket_lib_init();
   }
   numberOfSocketClients++;
}

void
WHBDeinitializeSocketLibrary()
{
   if(numberOfSocketClients > 0) {
      numberOfSocketClients--;
   }
   if(isSocketInitialized && numberOfSocketClients == 0) {
      isSocketInitialized = FALSE;
      socket_lib_finish();
   }
}
