#include "devoptab_sd.h"

int
__wut_fs_rename(struct _reent *r,
                const char *oldName,
                const char *newName)
{
   FSStatus  rc;

   if (oldName == NULL) {
      return -1;
   }

   if (newName == NULL) {
      return -1;
   }

   char *path_old = __wut_fs_fixpath(r, oldName);

   if (!path_old) {
      r->_errno = ENOMEM;
      return -1;
   }

   char *path_new = __wut_fs_fixpath(r, newName);

   if (!path_new) {
      r->_errno = ENOMEM;
      return -1;
   }

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSRename(__wut_devoptab_sd_client, &fsCmd, path_old, path_new, -1);
   free(path_old);
   free(path_new);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
