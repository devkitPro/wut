#pragma once
#include <wut.h>
#include <stdint.h>

#define FD_SETSIZE 32
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

#define SOL_SOCKET      -1

#define INADDR_ANY       0
#define INADDR_BROADCAST 0xFFFFFFFF

#define PF_UNSPEC       0
#define PF_INET         2
#define PF_INET6        23

#define AF_UNSPEC       PF_UNSPEC
#define AF_INET         PF_INET
#define AF_INET6        PF_INET6

#define SOCK_STREAM     1
#define SOCK_DGRAM      2

#define MSG_OOB         0x0001
#define MSG_PEEK        0x0002
#define MSG_DONTROUTE   0x0004
#define MSG_DONTWAIT    0x0020

#define SHUT_RD         0
#define SHUT_WR         1
#define SHUT_RDWR       2

#define IPPROTO_IP      0
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17

/*
 * SOL_SOCKET options
 */
#define SO_REUSEADDR    0x0004      // reuse address
#define SO_BROADCAST    0x0020      // broadcast
#define SO_LINGER       0x0080      // linger (no effect?)
#define SO_OOBINLINE    0x0100      // out-of-band data inline (no effect?)
#define SO_TCPSACK      0x0200      // set tcp selective acknowledgment
#define SO_WINSCALE     0x0400      // set tcp window scaling
#define SO_SNDBUF       0x1001      // send buffer size
#define SO_RCVBUF       0x1002      // receive buffer size
#define SO_SNDLOWAT     0x1003      // send low-water mark (no effect?)
#define SO_RCVLOWAT     0x1004      // receive low-water mark
#define SO_TYPE         0x1008      // get socket type
#define SO_ERROR        0x1009      // get socket error
#define SO_NBIO         0x1014      // set socket to NON-blocking mode
#define SO_BIO          0x1015      // set socket to blocking mode
#define SO_NONBLOCK     0x1016      // set/get blocking mode via optval param

/*
 * Errors returned by nsysnet socket functions
 * WARNING: these do not match with sys/errno.h (where EAGAIN is 11 for example).
 */
#define NSN_EAGAIN          6
#define NSN_EWOULDBLOCK     6

typedef uint32_t socklen_t;
typedef uint16_t sa_family_t;

struct sockaddr
{
   sa_family_t sa_family;
   char sa_data[];
};

struct sockaddr_storage
{
   sa_family_t ss_family;
   char ss_padding[14];
};

struct linger
{
   int l_onoff;
   int l_linger;
};

struct in_addr
{
   unsigned int s_addr;
};

struct sockaddr_in
{
   unsigned short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};

void
socket_lib_init();

void
socket_lib_finish();

int
accept(int sockfd,
       struct sockaddr *addr,
       socklen_t *addrlen);

int
bind(int sockfd,
     const struct sockaddr *addr,
     socklen_t addrlen);

int
socketclose(int sockfd);

int
connect(int sockfd,
        const struct sockaddr *addr,
        socklen_t addrlen);

int
getpeername(int sockfd,
            struct sockaddr *addr,
            socklen_t *addrlen);

int
getsockname(int sockfd,
            struct sockaddr *addr,
            socklen_t *addrlen);

int
getsockopt(int sockfd,
           int level,
           int optname,
           void *optval,
           socklen_t *optlen);

int
listen(int sockfd,
       int backlog);

int
recv(int sockfd,
     void *buf,
     size_t len,
     int flags);

int
recvfrom(int sockfd,
         void *buf,
         size_t len,
         int flags,
         struct sockaddr *src_addr,
         socklen_t *addrlen);

int
send(int sockfd,
     const void *buf,
     size_t len,
     int flags);

int
sendto(int sockfd,
       const void *buf,
       size_t len,
       int flags,
       const struct sockaddr *dest_addr,
       socklen_t addrlen);

int
setsockopt(int sockfd,
           int level,
           int optname,
           const void *optval,
           socklen_t optlen);

int
shutdown(int sockfd,
         int how);

int
socket(int domain,
       int type,
       int protocol);

int
select(int nfds,
       fd_set *readfds,
       fd_set *writefds,
       fd_set *exceptfds,
       struct timeval *timeout);

const char *
inet_ntoa(struct in_addr in);

char *
inet_ntoa_r(struct in_addr in, char *buf);

const char *
inet_ntop(int af, const void *src, char *dst, socklen_t size);

int
inet_pton(int af, const char *src, void *dst);

int
inet_aton(const char *cp, struct in_addr *inp);

int
socketlasterr();

uint32_t
htonl(uint32_t val);

uint16_t
htons(uint16_t val);

uint32_t
ntohl(uint32_t val);

uint16_t
ntohs(uint16_t val);

#ifdef __cplusplus
}
#endif

/** @} */
