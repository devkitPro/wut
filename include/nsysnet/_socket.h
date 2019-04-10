#pragma once
#include <wut.h>
#include <stdint.h>

#define NSYSNET_FD_SETSIZE 32
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

/**
 * \defgroup nsysnet_socket Socket
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

#define NSYSNET_C(func) __rplwrap_##func

#define NSYSNET_SOL_SOCKET      -1

#define NSYSNET_INADDR_ANY       0
#define NSYSNET_INADDR_BROADCAST 0xFFFFFFFF

#define NSYSNET_PF_UNSPEC       0
#define NSYSNET_PF_INET         2
#define NSYSNET_PF_INET6        23

#define NSYSNET_AF_UNSPEC       PF_UNSPEC
#define NSYSNET_AF_INET         PF_INET
#define NSYSNET_AF_INET6        PF_INET6

#define NSYSNET_SOCK_STREAM     1
#define NSYSNET_SOCK_DGRAM      2

#define NSYSNET_MSG_OOB         0x0001
#define NSYSNET_MSG_PEEK        0x0002
#define NSYSNET_MSG_DONTROUTE   0x0004
#define NSYSNET_MSG_DONTWAIT    0x0020

#define NSYSNET_SHUT_RD         0
#define NSYSNET_SHUT_WR         1
#define NSYSNET_SHUT_RDWR       2

#define NSYSNET_IPPROTO_IP      0
#define NSYSNET_IPPROTO_TCP     6
#define NSYSNET_IPPROTO_UDP     17

/*
 * SOL_SOCKET options
 */
#define NSYSNET_SO_REUSEADDR    0x0004      // reuse address
#define NSYSNET_SO_BROADCAST    0x0020      // broadcast
#define NSYSNET_SO_LINGER       0x0080      // linger (no effect?)
#define NSYSNET_SO_OOBINLINE    0x0100      // out-of-band data inline (no effect?)
#define NSYSNET_SO_TCPSACK      0x0200      // set tcp selective acknowledgment
#define NSYSNET_SO_WINSCALE     0x0400      // set tcp window scaling
#define NSYSNET_SO_SNDBUF       0x1001      // send buffer size
#define NSYSNET_SO_RCVBUF       0x1002      // receive buffer size
#define NSYSNET_SO_SNDLOWAT     0x1003      // send low-water mark (no effect?)
#define NSYSNET_SO_RCVLOWAT     0x1004      // receive low-water mark
#define NSYSNET_SO_TYPE         0x1008      // get socket type
#define NSYSNET_SO_ERROR        0x1009      // get socket error
#define NSYSNET_SO_NBIO         0x1014      // set socket to NON-blocking mode
#define NSYSNET_SO_BIO          0x1015      // set socket to blocking mode
#define NSYSNET_SO_NONBLOCK     0x1016      // set/get blocking mode via optval param

/*
 * Errors returned by nsysnet socket functions
 * WARNING: these do not match with sys/errno.h (where EAGAIN is 11 for example).
 */
#define NSYSNET_NSN_EAGAIN          6
#define NSYSNET_NSN_EWOULDBLOCK     6

typedef uint32_t nsysnet_socklen_t;
typedef uint16_t nsysnet_sa_family_t;

struct nsysnet_sockaddr
{
   nsysnet_sa_family_t sa_family;
   char sa_data[];
};

struct nsysnet_sockaddr_storage
{
   nsysnet_sa_family_t ss_family;
   char ss_padding[14];
};

struct nsysnet_linger
{
   int l_onoff;
   int l_linger;
};

struct nsysnet_in_addr
{
   unsigned int s_addr;
};

struct nsysnet_sockaddr_in
{
   unsigned short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};

void
NSYSNET_C(socket_lib_init)();

void
NSYSNET_C(socket_lib_finish)();

int
NSYSNET_C(accept)(int sockfd,
                  struct nsysnet_sockaddr *addr,
                  nsysnet_socklen_t *addrlen);

int
NSYSNET_C(bind)(int sockfd,
                const struct nsysnet_sockaddr *addr,
                nsysnet_socklen_t addrlen);

int
NSYSNET_C(socketclose)(int sockfd);

int
NSYSNET_C(connect)(int sockfd,
                   const struct nsysnet_sockaddr *addr,
                   nsysnet_socklen_t addrlen);

int
NSYSNET_C(getpeername)(int sockfd,
                       struct nsysnet_sockaddr *addr,
                       nsysnet_socklen_t *addrlen);

int
NSYSNET_C(getsockname)(int sockfd,
                       struct nsysnet_sockaddr *addr,
                       nsysnet_socklen_t *addrlen);

int
NSYSNET_C(getsockopt)(int sockfd,
                      int level,
                      int optname,
                      void *optval,
                      nsysnet_socklen_t *optlen);

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
                    struct nsysnet_sockaddr *src_addr,
                    nsysnet_socklen_t *addrlen);

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
                  const struct nsysnet_sockaddr *dest_addr,
                  nsysnet_socklen_t addrlen);

int
NSYSNET_C(setsockopt)(int sockfd,
                      int level,
                      int optname,
                      const void *optval,
                      nsysnet_socklen_t optlen);

int
NSYSNET_C(shutdown)(int sockfd,
                    int how);

int
NSYSNET_C(socket)(int domain,
                  int type,
                  int protocol);

//TODO not sure this can be made to work
/*int
NSYSNET_C(select)(int nfds,
                  fd_set *readfds,
                  fd_set *writefds,
                  fd_set *exceptfds,
                  struct timeval *timeout);*/

const char *
NSYSNET_C(inet_ntoa)(struct nsysnet_in_addr in);

char *
NSYSNET_C(inet_ntoa_r)(struct nsysnet_in_addr in,
                       char *buf);

const char *
NSYSNET_C(inet_ntop)(int af,
                     const void *src,
                     char *dst,
                     nsysnet_socklen_t size);

int
NSYSNET_C(inet_pton)(int af,
                     const char *src,
                     void *dst);

int
NSYSNET_C(inet_aton)(const char *cp,
                     struct nsysnet_in_addr *inp);

int
NSYSNET_C(socketlasterr)();

uint32_t
NSYSNET_C(htonl)(uint32_t val);

uint16_t
NSYSNET_C(htons)(uint16_t val);

uint32_t
NSYSNET_C(ntohl)(uint32_t val);

uint16_t
NSYSNET_C(ntohs)(uint16_t val);

#ifdef __cplusplus
}
#endif

/** @} */
