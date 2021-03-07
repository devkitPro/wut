#include "wut_socket.h"

static devoptab_t
__wut_socket_devoptab =
{
   .name = "sock",
   .structSize   = sizeof(int),
   .open_r       = __wut_socket_open,
   .close_r      = __wut_socket_close,
   .write_r      = __wut_socket_write,
   .read_r       = __wut_socket_read,
   .seek_r       = NULL,
   .fstat_r      = NULL,
   .stat_r       = NULL,
   .link_r       = NULL,
   .unlink_r     = NULL,
   .chdir_r      = NULL,
   .rename_r     = NULL,
   .mkdir_r      = NULL,
   .dirStateSize = 0,
   .diropen_r    = NULL,
   .dirreset_r   = NULL,
   .dirnext_r    = NULL,
   .dirclose_r   = NULL,
   .statvfs_r    = NULL,
   .ftruncate_r  = NULL,
   .fsync_r      = NULL,
   .deviceData   = 0,
   .chmod_r      = NULL,
   .fchmod_r     = NULL,
   .rmdir_r      = NULL,
};

static BOOL
__wut_socket_initialised = FALSE;

void
__init_wut_socket()
{
   BOOL connected = FALSE;
   int dev;

   if (__wut_socket_initialised) {
      return;
   }

   ACInitialize();
   ACConnect();

   ACIsApplicationConnected(&connected);
   if (!connected) {
      ACFinalize();
      return;
   }

   RPLWRAP(socket_lib_init)();

   dev = AddDevice(&__wut_socket_devoptab);
   if (dev == -1) {
      RPLWRAP(socket_lib_finish)();
      ACFinalize();
      return;
   }

   __wut_socket_initialised = TRUE;
}

void
__fini_wut_socket()
{
   if (!__wut_socket_initialised) {
      return;
   }

   RPLWRAP(socket_lib_finish)();
   ACFinalize();

   __wut_socket_initialised = FALSE;
}

