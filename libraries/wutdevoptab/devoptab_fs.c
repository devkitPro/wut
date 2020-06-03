#include "devoptab_fs.h"

static devoptab_t
__wut_fs_devoptab =
{
   .name         = "fs",
   .structSize   = sizeof(__wut_fs_file_t),
   .open_r       = __wut_fs_open,
   .close_r      = __wut_fs_close,
   .write_r      = __wut_fs_write,
   .read_r       = __wut_fs_read,
   .seek_r       = __wut_fs_seek,
   .fstat_r      = __wut_fs_fstat,
   .stat_r       = __wut_fs_stat,
   .link_r       = __wut_fs_link,
   .unlink_r     = __wut_fs_unlink,
   .chdir_r      = __wut_fs_chdir,
   .rename_r     = __wut_fs_rename,
   .mkdir_r      = __wut_fs_mkdir,
   .dirStateSize = sizeof(__wut_fs_dir_t),
   .diropen_r    = __wut_fs_diropen,
   .dirreset_r   = __wut_fs_dirreset,
   .dirnext_r    = __wut_fs_dirnext,
   .dirclose_r   = __wut_fs_dirclose,
   .statvfs_r    = __wut_fs_statvfs,
   .ftruncate_r  = __wut_fs_ftruncate,
   .fsync_r      = __wut_fs_fsync,
   .deviceData   = NULL,
   .chmod_r      = __wut_fs_chmod,
   .fchmod_r     = __wut_fs_fchmod,
   .rmdir_r      = __wut_fs_rmdir,
};

FSClient *
__wut_devoptab_fs_client = NULL;

static BOOL
__wut_fs_initialised = FALSE;

FSStatus
__init_wut_devoptab()
{
   FSStatus rc = 0;

   if (__wut_fs_initialised) {
      return rc;
   }

   __wut_devoptab_fs_client = memalign(0x20, sizeof(FSClient));
   FSCmdBlock fsCmd;
   FSMountSource mountSource;
   char mountPath[0x80];
   char workDir[0x83];

   FSInit();
   rc = FSAddClient(__wut_devoptab_fs_client, -1);

   if (rc < 0) {
      free(__wut_devoptab_fs_client);
      return rc;
   }

   FSInitCmdBlock(&fsCmd);

   if (rc >= 0) {
      int dev = AddDevice(&__wut_fs_devoptab);

      if(dev != -1) {
         setDefaultDevice(dev);
         __wut_fs_initialised = TRUE;

         // Mount the SD card
         rc = FSGetMountSource(__wut_devoptab_fs_client, &fsCmd, FS_MOUNT_SOURCE_SD, &mountSource, -1);

         if (rc < 0) {
            return rc;
         }

         rc = FSMount(__wut_devoptab_fs_client, &fsCmd, &mountSource, mountPath, 0x80, -1);

         if (rc >= 0) {
            // chdir to SD root for general use
            strcpy(workDir, "fs:");
            strcat(workDir, mountPath);
            chdir(workDir);
         }
      } else {
         FSDelClient(__wut_devoptab_fs_client, -1);
         free(__wut_devoptab_fs_client);
         return dev;
      }
   }

   return rc;
}

FSStatus
__fini_wut_devoptab()
{
   FSStatus rc = 0;

   if (!__wut_fs_initialised) {
      return rc;
   }

   FSDelClient(__wut_devoptab_fs_client, -1);
   free(__wut_devoptab_fs_client);
   
   RemoveDevice(__wut_fs_devoptab.name);
   
   __wut_devoptab_fs_client = NULL;   
   __wut_fs_initialised = FALSE;
   
   return rc;
}
