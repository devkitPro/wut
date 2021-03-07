#include "wut_socket.h"

int
poll(struct pollfd *fds,
     nfds_t nfds,
     int timeout)
{
   int cnv_nfds = 0, rc, i;
   nsysnet_fd_set cnv_rd, cnv_wr, cnv_ex;
   struct nsysnet_timeval cnv_timeout;

   if (!fds) {
      errno = EINVAL;
      return -1;
   }

   NSYSNET_FD_ZERO(&cnv_rd);
   NSYSNET_FD_ZERO(&cnv_wr);
   NSYSNET_FD_ZERO(&cnv_ex);

   for (i = 0; i < nfds; i++) {
      int cnv_fd;

      if (fds[i].fd < 0) {
         continue;
      }

      cnv_fd = __wut_get_nsysnet_fd(fds[i].fd);
      if (cnv_fd == -1) {
         return -1;
      }

      if ((cnv_fd + 1) > cnv_nfds) {
         cnv_nfds = cnv_fd + 1;
      }

      if (fds[i].events & POLLIN) {
         NSYSNET_FD_SET(cnv_fd, &cnv_rd);
      }
      if (fds[i].events & POLLOUT) {
         NSYSNET_FD_SET(cnv_fd, &cnv_wr);
      }
      if (fds[i].events & POLLPRI) {
         NSYSNET_FD_SET(cnv_fd, &cnv_ex);
      }
   }

   if (timeout >= 0) {
      cnv_timeout.tv_sec  = timeout / 1000;
      cnv_timeout.tv_usec = (timeout % 1000) * 1000;
   }

   rc = RPLWRAP(select)(cnv_nfds, &cnv_rd, &cnv_wr, &cnv_ex,
                        (timeout >= 0) ? &cnv_timeout : NULL);

   rc = __wut_get_nsysnet_result(NULL, rc);
   if (rc == -1) {
      return rc;
   }

   for (i = 0; i < nfds; i++) {
      int cnv_fd;

      fds[i].revents = 0;

      if (fds[i].fd < 0) {
         continue;
      }

      cnv_fd = __wut_get_nsysnet_fd(fds[i].fd);
      if (cnv_fd == -1) {
         continue;
      }

      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_rd)) {
         fds[i].revents |= POLLIN;
      }
      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_wr)) {
         fds[i].revents |= POLLOUT;
      }
      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_ex)) {
         fds[i].revents |= POLLPRI;
      }
   }

   return rc;
}
