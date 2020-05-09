/*
 * Copyright (C) 2015-2020 exjam <james.benton2@gmail.com>
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
