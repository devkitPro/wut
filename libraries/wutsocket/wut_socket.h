#pragma once
#include <fcntl.h>
#include <nn/ac.h>
#include <nsysnet/_socket.h>
#include <poll.h>
#include <stdarg.h>
#include <string.h>
#include <sys/iosupport.h>
#include <sys/select.h>
#define __LINUX_ERRNO_EXTENSIONS__
#include <errno.h>

int
__wut_get_nsysnet_fd(int fd);
int
__wut_get_nsysnet_result(struct _reent *r, int rc);

int
__wut_socket_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode);
int
__wut_socket_close(struct _reent *r, void *fd);
ssize_t
__wut_socket_write(struct _reent *r, void *fd, const char *ptr, size_t len);
ssize_t
__wut_socket_read(struct _reent *r, void *fd, char *ptr, size_t len);
