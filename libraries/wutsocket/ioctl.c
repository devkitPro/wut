#include "wut_socket.h"
#include <sys/ioctl.h>

int ioctl(int fd,
          int request,
          ...)
{
   void *data;
   va_list args;
   int sockfd;
   int rc;

   va_start(args, request);
   data = (request & IOC_INOUT) ? va_arg(args, void *) : NULL;
   va_end(args);

   if (data == NULL && (request & IOC_INOUT) && IOCPARM_LEN(request) != 0) {
      errno = EFAULT;
      return -1;
   }

   sockfd = __wut_get_nsysnet_fd(fd);
   if (sockfd == -1) {
      return -1;
   }

   switch (request) {
      case FIONBIO: {
         int flags = fcntl(fd, F_GETFL, 0);
         if (flags == -1) {
            return -1;
         }
         flags = *(int *) data != 0 ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
         return fcntl(fd, F_SETFL, flags);
      }
      case FIONREAD: {
         socklen_t optlen = sizeof(int32_t);
         rc               = RPLWRAP(getsockopt)(sockfd,
                                  SOL_SOCKET,
                                  SO_RXDATA,
                                  data,
                                  &optlen);
         return __wut_get_nsysnet_result(NULL, rc);
      }
      case FIONWRITE: {
         socklen_t optlen = sizeof(int32_t);
         rc               = RPLWRAP(getsockopt)(sockfd,
                                  SOL_SOCKET,
                                  SO_TXDATA,
                                  data,
                                  &optlen);
         return __wut_get_nsysnet_result(NULL, rc);
      }
      default:
         break;
   }

   return -1;
}
