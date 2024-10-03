#pragma once
#include <wut.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#warning "nsysnet/socket.h is deprecated; please use standard socket headers instead."

#ifdef __cplusplus
extern "C" {
#endif

#define NSN_EAGAIN      EAGAIN
#define NSN_EWOULDBLOCK EWOULDBLOCK

__attribute__((deprecated)) static inline int
socketclose(int sockfd)
{
   return close(sockfd);
}

__attribute__((deprecated)) static inline int
socketlasterr()
{
   return errno;
}

#ifdef __cplusplus
}
#endif
