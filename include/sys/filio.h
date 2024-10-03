#pragma once

#include <sys/ioccom.h>

/* Generic file-descriptor ioctl's. */
#define FIOCLEX   _IO('f', 1)         /* set close on exec on fd */
#define FIONCLEX  _IO('f', 2)         /* remove close on exec */
#define FIONREAD  _IOR('f', 127, int) /* get # bytes to read */
#define FIONWRITE _IOR('f', 119, int) /* get # bytes (yet) to write */
#define FIONBIO   _IOW('f', 126, int) /* set/clear non-blocking i/o */
#define FIOASYNC  _IOW('f', 125, int) /* set/clear async i/o */
#define FIOSETOWN _IOW('f', 124, int) /* set owner */
#define FIOGETOWN _IOR('f', 123, int) /* get owner */
#define FIODTYPE  _IOR('f', 122, int) /* get d_flags type part */
#define FIOGETLBA _IOR('f', 121, int) /* get start blk # */
struct fiodgname_arg
{
   int len;
   void *buf;
};
#define FIODGNAME _IOW('f', 120, struct fiodgname_arg) /* get dev. name */
#define FIONSPACE _IOR('f', 118, int)                  /* get space in send queue */
