#include "devoptab_fs.h"

int
__wut_fs_dirreset(struct _reent *r,
                  DIR_ITER *dirState)
{
   FSStatus rc;

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   __wut_fs_dir_t *dir = (__wut_fs_dir_t *)(dirState->dirStruct);
   rc = FSRewindDir(__wut_devoptab_fs_client, &fsCmd, dir->fd, -1);

   if (rc >= 0) {
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}

