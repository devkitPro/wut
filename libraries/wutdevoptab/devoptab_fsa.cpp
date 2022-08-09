#include "devoptab_fsa.h"
#include <cstdio>

static devoptab_t
        __wut_fsa_devoptab =
        {
                .name         = "fs",
                .structSize   = sizeof(__wut_fsa_file_t),
                .open_r       = __wut_fsa_open,
                .close_r      = __wut_fsa_close,
                .write_r      = __wut_fsa_write,
                .read_r       = __wut_fsa_read,
                .seek_r       = __wut_fsa_seek,
                .fstat_r      = __wut_fsa_fstat,
                .stat_r       = __wut_fsa_stat,
                .unlink_r     = __wut_fsa_unlink,
                .chdir_r      = __wut_fsa_chdir,
                .rename_r     = __wut_fsa_rename,
                .mkdir_r      = __wut_fsa_mkdir,
                .dirStateSize = sizeof(__wut_fsa_dir_t),
                .diropen_r    = __wut_fsa_diropen,
                .dirreset_r   = __wut_fsa_dirreset,
                .dirnext_r    = __wut_fsa_dirnext,
                .dirclose_r   = __wut_fsa_dirclose,
                .statvfs_r    = __wut_fsa_statvfs,
                .ftruncate_r  = __wut_fsa_ftruncate,
                .fsync_r      = __wut_fsa_fsync,
                .deviceData   = nullptr,
                .chmod_r      = __wut_fsa_chmod,
                .rmdir_r      = __wut_fsa_rmdir,
                .lstat_r      = __wut_fsa_stat,
        };


__wut_fsa_device_t __wut_fsa_device_data = {};

FSError __init_wut_devoptab() {
   FSError rc;

   if (__wut_fsa_device_data.setup) {
      return FS_ERROR_OK;
   }

   __wut_fsa_device_data = {};
   memcpy(&__wut_fsa_device_data.device, &__wut_fsa_devoptab, sizeof(__wut_fsa_devoptab));
   __wut_fsa_device_data.device.deviceData = &__wut_fsa_device_data;
   snprintf(__wut_fsa_device_data.name, sizeof(__wut_fsa_device_data.name), "fs");
   __wut_fsa_device_data.device.name = __wut_fsa_device_data.name;
   __wut_fsa_device_data.setup = false;
   __wut_fsa_device_data.mounted = false;
   __wut_fsa_device_data.isSDCard = false;

   FSAInit();
   __wut_fsa_device_data.clientHandle = FSAAddClient(nullptr);
   if (__wut_fsa_device_data.clientHandle == 0) {
      WUT_DEBUG_REPORT("FSAAddClient() failed");
      return FS_ERROR_MAX_CLIENTS;
   }

   int dev = AddDevice(&__wut_fsa_device_data.device);

   if (dev != -1) {
      setDefaultDevice(dev);
      __wut_fsa_device_data.setup = true;
      snprintf(__wut_fsa_device_data.mountPath, sizeof(__wut_fsa_device_data.mountPath), "/vol/external01");

      rc = FSAMount(__wut_fsa_device_data.clientHandle, "/dev/sdcard01", __wut_fsa_device_data.mountPath, (FSAMountFlags) 0, nullptr, 0);

      if (rc < 0 && rc != FS_ERROR_ALREADY_EXISTS) {
         WUT_DEBUG_REPORT("FSAMount(0x%08X, \"/dev/sdcard01\", %s, %08X, %08X, %08X) failed: %s\n",
                          __wut_fsa_device_data.clientHandle, __wut_fsa_device_data.mountPath, 0, nullptr, 0, FSAGetStatusStr(rc));
         return rc;
      }

      __wut_fsa_device_data.isSDCard = true;
      __wut_fsa_device_data.mounted = true;
      __wut_fsa_device_data.cwd[0] = '/';
      __wut_fsa_device_data.cwd[1] = '\0';
      chdir("fs:/vol/external01");

      FSADeviceInfo deviceInfo;
      if ((rc = FSAGetDeviceInfo(__wut_fsa_device_data.clientHandle, __wut_fsa_device_data.mountPath, &deviceInfo)) >= 0) {
         __wut_fsa_device_data.deviceSizeInSectors = deviceInfo.deviceSizeInSectors;
         __wut_fsa_device_data.deviceSectorSize = deviceInfo.deviceSectorSize;
      } else {
         __wut_fsa_device_data.deviceSizeInSectors = 0xFFFFFFFF;
         __wut_fsa_device_data.deviceSectorSize = 512;
         WUT_DEBUG_REPORT("Failed to get DeviceInfo for %s: %s\n", __wut_fsa_device_data.mountPath, FSAGetStatusStr(rc));
      }

   } else {
      FSADelClient(__wut_fsa_device_data.clientHandle);
      __wut_fsa_device_data.clientHandle = 0;
      return FS_ERROR_MAX_CLIENTS;
   }

   return FS_ERROR_OK;
}

FSError
__fini_wut_devoptab() {
   FSError rc = FS_ERROR_OK;

   if (!__wut_fsa_device_data.setup) {
      return rc;
   }

   if (__wut_fsa_device_data.mounted) {
      FSAUnmount(__wut_fsa_device_data.clientHandle, __wut_fsa_device_data.mountPath, FSA_UNMOUNT_FLAG_BIND_MOUNT);
      __wut_fsa_device_data.mounted = false;
   }

   FSADelClient(__wut_fsa_device_data.clientHandle);

   RemoveDevice(__wut_fsa_device_data.device.name);

   __wut_fsa_device_data = {};

   return rc;
}
