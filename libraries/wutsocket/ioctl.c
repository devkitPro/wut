#include "wut_socket.h"
#include <sys/ioctl.h>

int
ioctl(int fd,
      int request,
      ...)
{
   va_list args;
   int sockfd;
   int rc;

   sockfd = __wut_get_nsysnet_fd(fd);
   if (sockfd == -1) {
      return -1;
   }

   switch(request) {
      case FIONBIO: {
         va_start(args, request);
         int *data = va_arg(args, int *);
         va_end(args);

         if(data == NULL) {
            errno = EFAULT;
            return -1;
         }

         int flags = fcntl(fd, F_GETFL, 0);
         if(flags == -1) {
            return -1;
         }
         flags = (*data != 0) ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
         return fcntl(fd, F_SETFL, flags);
      }
      case FIONREAD:
      case FIONWRITE: {
         socklen_t optlen = sizeof(int32_t);
         va_start(args, request);
         int32_t *data = va_arg(args, int32_t *);
         va_end(args);

         if(data == NULL) {
            errno = EFAULT;
            return -1;
         }

         rc = RPLWRAP(getsockopt)(sockfd,
                                  SOL_SOCKET,
                                  (request == FIONREAD) ? SO_RXDATA : SO_TXDATA,
                                  data,
                                  &optlen);
         return __wut_get_nsysnet_result(NULL, rc);
      }
      default:
         errno = ENOTTY;
         break;
   }

   return -1;
}
