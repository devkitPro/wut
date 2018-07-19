#include "devoptab_fs.h"

int
__wut_fs_chdir(struct _reent *r,
               const char *name)
{
   FSStatus rc;

   if (name == NULL) {
         return -1;
   }

   char *path = __wut_fs_fixpath(r, name);

   if (!path) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSChangeDir(__wut_devoptab_fs_client, &fsCmd, path, -1);
   free(path);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
