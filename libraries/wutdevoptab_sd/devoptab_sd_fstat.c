#include "devoptab_sd.h"

int
__wut_fs_fstat(struct _reent *r,
               void *fd,
               struct stat *st)
{
   FSStatus rc;
   FSStat fsstat;
   __wut_fs_file_t *file = (__wut_fs_file_t *)fd;

   // Set up command block
   FSCmdBlock fsCmd;
   FSInitCmdBlock(&fsCmd);

   rc = FSGetStatFile(__wut_devoptab_sd_client, &fsCmd, file->fd, &fsstat, -1);

   if (rc >= 0) {
      memset(st, 0, sizeof(struct stat));
      st->st_size = fsstat.size;
      st->st_uid = fsstat.owner;
      st->st_gid = fsstat.group;
      st->st_nlink = 1;
      st->st_mode = fsstat.mode;
      return 0;
   }

   r->_errno = __wut_fs_translate_error(rc);
   return -1;
}
