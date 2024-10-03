#pragma once
#include <wut.h>
#include <wut_rplwrap.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

/**
 * \defgroup nsysnet_socket Socket
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * fd_set for select()
 */
#define NSYSNET_FD_SETSIZE     32

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
socket_lib_init();

void
socket_lib_finish();

// clang-format off

int
RPLWRAP(accept)(int sockfd,
                struct sockaddr *addr,
                socklen_t *addrlen);

int
RPLWRAP(bind)(int sockfd,
              const struct sockaddr *addr,
              socklen_t addrlen);

int
RPLWRAP(socketclose)(int sockfd);

int
RPLWRAP(connect)(int sockfd,
                 const struct sockaddr *addr,
                 socklen_t addrlen);

int
RPLWRAP(getpeername)(int sockfd,
                     struct sockaddr *addr,
                     socklen_t *addrlen);

int
RPLWRAP(getsockname)(int sockfd,
                     struct sockaddr *addr,
                     socklen_t *addrlen);

int
RPLWRAP(getsockopt)(int sockfd,
                    int level,
                    int optname,
                    void *optval,
                    socklen_t *optlen);

int
RPLWRAP(listen)(int sockfd,
                int backlog);

int
RPLWRAP(recv)(int sockfd,
              void *buf,
              size_t len,
              int flags);

int
RPLWRAP(recvfrom)(int sockfd,
                  void *buf,
                  size_t len,
                  int flags,
                  struct sockaddr *src_addr,
                  socklen_t *addrlen);

int
RPLWRAP(send)(int sockfd,
              const void *buf,
              size_t len,
              int flags);

int
RPLWRAP(sendto)(int sockfd,
                const void *buf,
                size_t len,
                int flags,
                const struct sockaddr *dest_addr,
                socklen_t addrlen);

int
RPLWRAP(setsockopt)(int sockfd,
                    int level,
                    int optname,
                    const void *optval,
                    socklen_t optlen);

int
RPLWRAP(shutdown)(int sockfd,
                  int how);

int
RPLWRAP(socket)(int domain,
                int type,
                int protocol);

int
RPLWRAP(select)(int nfds,
                nsysnet_fd_set *readfds,
                nsysnet_fd_set *writefds,
                nsysnet_fd_set *exceptfds,
                struct nsysnet_timeval *timeout);

const char *
RPLWRAP(inet_ntop)(int af,
                   const void *src,
                   char *dst,
                   socklen_t size);

int
RPLWRAP(inet_pton)(int af,
                   const char *src,
                   void *dst);

int
RPLWRAP(socketlasterr)();

// clang-format on

#ifdef __cplusplus
}
#endif

/** @} */
