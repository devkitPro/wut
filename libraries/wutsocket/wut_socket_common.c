#include "wut_socket.h"

#define NSYSNET_UNKNOWN_ERROR_OFFSET 10000

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

