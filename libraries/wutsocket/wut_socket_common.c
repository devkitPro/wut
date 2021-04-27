#include "wut_socket.h"

#define NSYSNET_UNKNOWN_ERROR_OFFSET 10000

int h_errno;

static uint32_t
__wut_socket_refcount = 0;

static devoptab_t
__wut_socket_devoptab =
{
   .name         = "soc",
   .structSize   = sizeof(int),
   .open_r       = __wut_socket_open,
   .close_r      = __wut_socket_close,
   .write_r      = __wut_socket_write,
   .read_r       = __wut_socket_read,
};

static unsigned char
__wut_nsysnet_error_code_map[] =
{
   0, // 0
   ENOBUFS,
   ETIMEDOUT,
   EISCONN,
   EOPNOTSUPP,
   ECONNABORTED, // 5
   EWOULDBLOCK,
   ECONNREFUSED,
   ECONNRESET,
   ENOTCONN,
   EALREADY, // 10
   EINVAL,
   EMSGSIZE,
   EPIPE,
   EDESTADDRREQ,
   ESHUTDOWN, // 15
   ENOPROTOOPT,
   EBUSY,
   ENOMEM,
   EADDRNOTAVAIL,
   EADDRINUSE, // 20
   EAFNOSUPPORT,
   EINPROGRESS,
   EIO,
   ENOTSOCK,
   EINVAL, // 25
   EINVAL,
   EIO,
   ETOOMANYREFS,
   EFAULT,
   ENETUNREACH, // 30
   EPROTONOSUPPORT,
   EPROTOTYPE,
   EINVAL,
   EINVAL,
   EINVAL, // 35
   EINVAL,
   EINVAL,
   EINVAL,
   EINVAL,
   EINVAL, // 40
   EINVAL,
   ENODEV,
   EBUSY,
   EBUSY,
   EINVAL, // 45
   EINVAL,
   EINVAL,
   ENOMEM,
   EBADFD,
   ECANCELED, // 50
   EMFILE,
};

void
socket_lib_init()
{
   if (0 == __wut_socket_refcount++) {
      RPLWRAP(socket_lib_init)();
      AddDevice(&__wut_socket_devoptab);
   }
}

void
socket_lib_finish()
{
   if (0 == --__wut_socket_refcount) {
      RemoveDevice("soc:");
      RPLWRAP(socket_lib_finish)();
   }
}

void
WHBInitializeSocketLibrary() __attribute__((alias("socket_lib_init")));

void
WHBDeinitializeSocketLibrary() __attribute__((alias("socket_lib_finish")));

void __attribute__((weak))
__init_wut_socket()
{
   socket_lib_init();
   ACInitialize();
   ACConnectAsync();
}

void __attribute__((weak))
__fini_wut_socket()
{
   ACClose();
   ACFinalize();
   socket_lib_finish();
}

int
__wut_get_nsysnet_fd(int fd)
{
   __handle *handle = __get_handle(fd);
   if (handle == NULL) {
      errno = EBADF;
      return -1;
   }
   if (strcmp(devoptab_list[handle->device]->name, "soc") != 0) {
      errno = ENOTSOCK;
      return -1;
   }
   return *(int *)handle->fileStruct;
}

int
__wut_get_nsysnet_result(struct _reent *r,
                         int rc)
{
   int sockerror, error;

   if (rc >= 0) {
      return rc;
   }

   sockerror = RPLWRAP(socketlasterr)();

   if (sockerror < 0) {
      return -1;
   }

   if (sockerror < sizeof(__wut_nsysnet_error_code_map)) {
      error = __wut_nsysnet_error_code_map[sockerror];
   } else {
      error = NSYSNET_UNKNOWN_ERROR_OFFSET + sockerror;
   }

   if (r) {
      r->_errno = error;
   } else {
      errno = error;
   }

   return -1;
}
