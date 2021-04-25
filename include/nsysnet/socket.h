#pragma once
#include <wut.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#warning "nsysnet/socket.h is deprecated; please use standard socket headers instead."

#ifdef __cplusplus
extern "C" {
#endif

#define NSN_EAGAIN          EAGAIN
#define NSN_EWOULDBLOCK     EWOULDBLOCK

__attribute__ ((deprecated))
static inline int
socketclose(int sockfd)
{
   return close(sockfd);
}

__attribute__ ((deprecated))
static inline int
socketlasterr()
{
   return errno;
}

#ifdef __cplusplus
}
#endif

