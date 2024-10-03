#include "wut_socket.h"

int
fcntl(int fd,
      int cmd,
      ...)
{
   va_list args;
   int sockfd, rc, flags, nonblock;
   socklen_t nonblock_len = sizeof(nonblock);

   if (cmd != F_GETFL && cmd != F_SETFL) {
      errno = EOPNOTSUPP;
      return -1;
   }

   sockfd = __wut_get_nsysnet_fd(fd);
   if (sockfd == -1) {
      return -1;
   }

   /* F_SETFL */
   if (cmd == F_SETFL) {
      va_start(args, cmd);
      flags = va_arg(args, int);
      va_end(args);

      nonblock = !!(flags & O_NONBLOCK);
      rc       = RPLWRAP(setsockopt)(sockfd,
                               SOL_SOCKET,
                               SO_NONBLOCK,
                               &nonblock,
                               nonblock_len);
      return __wut_get_nsysnet_result(NULL, rc);
   }

   /* F_GETFL */
   rc = RPLWRAP(getsockopt)(sockfd,
                            SOL_SOCKET,
                            SO_NONBLOCK,
                            &nonblock,
                            &nonblock_len);
   if (rc == -1) {
      return __wut_get_nsysnet_result(NULL, rc);
   }
   flags = (nonblock) ? O_NONBLOCK : 0;
   return flags;
}
