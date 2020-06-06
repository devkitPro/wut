#include "my_first_rpl.h"

#include <coreinit/dynload.h>

const char *
my_first_export()
{
   return "Hello from my_first_rpl!";
}

int
rpl_entry(OSDynLoad_Module module,
          OSDynLoad_EntryReason reason)
{
   if (reason == OS_DYNLOAD_LOADED) {
      // Do stuff on load
   } else if (reason == OS_DYNLOAD_UNLOADED) {
      // Do stuff on unload
   }

   return 0;
}
