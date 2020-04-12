#include "wut_socket.h"

int
select(int nfds,
       fd_set *readfds,
       fd_set *writefds,
       fd_set *exceptfds,
       struct timeval *timeout)
{
   int cnv_nfds = 0, rc, i;
   nsysnet_fd_set cnv_rd, cnv_wr, cnv_ex;
   struct nsysnet_timeval cnv_timeout;

   if (nfds > FD_SETSIZE) {
      errno = EINVAL;
      return -1;
   }

   NSYSNET_FD_ZERO(&cnv_rd);
   NSYSNET_FD_ZERO(&cnv_wr);
   NSYSNET_FD_ZERO(&cnv_ex);

   for (i = 0; i < nfds; i++) {
      int rd_fd, wr_fd, ex_fd, cnv_fd;

      rd_fd = readfds && FD_ISSET(i, readfds);
      wr_fd = writefds && FD_ISSET(i, writefds);
      ex_fd = exceptfds && FD_ISSET(i, exceptfds);

      if (!rd_fd && !wr_fd && !ex_fd) {
         continue;
      }

      cnv_fd = __wut_get_nsysnet_fd(i);
      if (cnv_fd == -1) {
         return -1;
      }

      if ((cnv_fd + 1) > cnv_nfds) {
         cnv_nfds = cnv_fd + 1;
      }

      if (rd_fd) {
         NSYSNET_FD_SET(cnv_fd, &cnv_rd);
      }
      if (wr_fd) {
         NSYSNET_FD_SET(cnv_fd, &cnv_wr);
      }
      if (ex_fd) {
         NSYSNET_FD_SET(cnv_fd, &cnv_ex);
      }
   }

   if (timeout) {
      cnv_timeout.tv_sec = timeout->tv_sec;
      cnv_timeout.tv_usec = timeout->tv_usec;
   }

   rc = NSYSNET_C(select)(cnv_nfds,
                          readfds ? &cnv_rd : NULL,
                          writefds ? &cnv_wr : NULL,
                          exceptfds ? &cnv_ex : NULL,
                          timeout ? &cnv_timeout : NULL);

   rc = __wut_get_nsysnet_result(NULL, rc);
   if (rc == -1) {
      return rc;
   }

   rc = 0;

   if (readfds) {
      FD_ZERO(readfds);
   }
   if (writefds) {
      FD_ZERO(writefds);
   }
   if (exceptfds) {
      FD_ZERO(exceptfds);
   }

   for (i = 0; i < nfds; i++) {
      int cnv_fd = __wut_get_nsysnet_fd(i);
      if (cnv_fd == -1) {
         continue;
      }

      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_rd)) {
         FD_SET(i, readfds);
         rc++;
      }
      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_wr)) {
         FD_SET(i, writefds);
         rc++;
      }
      if (NSYSNET_FD_ISSET(cnv_fd, &cnv_ex)) {
         FD_SET(i, exceptfds);
         rc++;
      }
   }

   return rc;
}
