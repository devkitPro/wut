#include <coreinit/dynload.h>

int
my_first_export()
{
   return 1;
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
