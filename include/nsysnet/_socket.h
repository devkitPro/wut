#pragma once
#include <wut.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * \defgroup nsysnet_socket Socket
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

#define NSYSNET_C(func) __rplwrap_##func

/*
 * fd_set for select()
 */
#define NSYSNET_FD_SETSIZE 32

#define NSYSNET_FD_SET(n, p)   ((p)->fds_bits |= (1L << (n)))
#define NSYSNET_FD_CLR(n, p)   ((p)->fds_bits &= ~(1L << (n)))
#define NSYSNET_FD_ISSET(n, p) ((p)->fds_bits & (1L << (n)))
#define NSYSNET_FD_ZERO(p)     ((p)->fds_bits = 0L)

typedef uint32_t nsysnet_fd_mask;
typedef struct nsysnet_fd_set nsysnet_fd_set;

struct nsysnet_fd_set
{
    nsysnet_fd_mask fds_bits;
};

struct nsysnet_timeval
{
    long tv_sec;
    long tv_usec;
};

void
NSYSNET_C(socket_lib_init)();

void
NSYSNET_C(socket_lib_finish)();

int
NSYSNET_C(accept)(int sockfd,
                  struct sockaddr *addr,
                  socklen_t *addrlen);

int
NSYSNET_C(bind)(int sockfd,
                const struct sockaddr *addr,
                socklen_t addrlen);

int
NSYSNET_C(socketclose)(int sockfd);

int
NSYSNET_C(connect)(int sockfd,
                   const struct sockaddr *addr,
                   socklen_t addrlen);

int
NSYSNET_C(getpeername)(int sockfd,
                       struct sockaddr *addr,
                       socklen_t *addrlen);

int
NSYSNET_C(getsockname)(int sockfd,
                       struct sockaddr *addr,
                       socklen_t *addrlen);

int
NSYSNET_C(getsockopt)(int sockfd,
                      int level,
                      int optname,
                      void *optval,
                      socklen_t *optlen);

int
NSYSNET_C(listen)(int sockfd,
                  int backlog);

int
NSYSNET_C(recv)(int sockfd,
                void *buf,
                size_t len,
                int flags);

int
NSYSNET_C(recvfrom)(int sockfd,
                    void *buf,
                    size_t len,
                    int flags,
                    struct sockaddr *src_addr,
                    socklen_t *addrlen);

int
NSYSNET_C(send)(int sockfd,
                const void *buf,
                size_t len,
                int flags);

int
NSYSNET_C(sendto)(int sockfd,
                  const void *buf,
                  size_t len,
                  int flags,
                  const struct sockaddr *dest_addr,
                  socklen_t addrlen);

int
NSYSNET_C(setsockopt)(int sockfd,
                      int level,
                      int optname,
                      const void *optval,
                      socklen_t optlen);

int
NSYSNET_C(shutdown)(int sockfd,
                    int how);

int
NSYSNET_C(socket)(int domain,
                  int type,
                  int protocol);

int
NSYSNET_C(select)(int nfds,
                  nsysnet_fd_set *readfds,
                  nsysnet_fd_set *writefds,
                  nsysnet_fd_set *exceptfds,
                  struct nsysnet_timeval *timeout);

const char *
NSYSNET_C(inet_ntop)(int af,
                     const void *src,
                     char *dst,
                     socklen_t size);

int
NSYSNET_C(inet_pton)(int af,
                     const char *src,
                     void *dst);

int
NSYSNET_C(socketlasterr)();

#ifdef __cplusplus
}
#endif

/** @} */
