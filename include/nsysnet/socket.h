#pragma once
#include <wut.h>
#include <stdint.h>

/**
 * \defgroup nsysnet_socket Socket
 * \ingroup nsysnet
 * @{
 */

#define SOL_SOCKET      -1

#define INADDR_ANY      0

#define PF_UNSPEC       0
#define PF_INET         2
#define PF_INET6        23

#define AF_UNSPEC       PF_UNSPEC
#define AF_INET         PF_INET
#define AF_INET6        PF_INET6

#define EAGAIN          6
#define EWOULDBLOCK     6

#define SOCK_STREAM     1
#define SOCK_DGRAM      2

#define MSG_OOB         0x0001
#define MSG_PEEK        0x0002
#define MSG_DONTWAIT    0x0004
#define MSG_DONTROUTE   0x0000  // ???
#define MSG_WAITALL     0x0000  // ???
#define MSG_MORE        0x0000  // ???
#define MSG_NOSIGNAL    0x0000  // there are no signals

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
#define SO_LINGER       0x0080      // linger (no effect?)
#define SO_OOBINLINE    0x0100      // out-of-band data inline (no effect?)
#define SO_SNDBUF       0x1001      // send buffer size
#define SO_RCVBUF       0x1002      // receive buffer size
#define SO_SNDLOWAT     0x1003      // send low-water mark (no effect?)
#define SO_RCVLOWAT     0x1004      // receive low-water mark
#define SO_TYPE         0x1008      // get socket type
#define SO_ERROR        0x1009      // get socket error
#define SO_NBIO         0x1014      // set socket to NON-blocking mode
#define SO_BIO          0x1015      // set socket to blocking mode
#define SO_NONBLOCK     0x1016      // set/get blocking mode via optval param

#define FD_SETSIZE (32)
#define FD_CLR(n, set) \
   ((set)->fd_bits &= ~(1 << (n)))
#define FD_COPY(src, set) \
   ((set)->fd_bits = (src)->fd_bits)
#define FD_ISSET(n, set) \
   ((set)->fd_bits & (1 << (n)))
#define FD_SET(n, set) \
   ((set)->fd_bits |= (1 << (n)))
#define FD_ZERO(n, set) \
   ((set)->fd_bits = 0)

typedef uint32_t socklen_t;
typedef uint16_t sa_family_t;
typedef uint32_t fd_mask;

typedef struct fd_set fd_set;

struct sockaddr
{
   sa_family_t sa_family;
   char        sa_data[];
};

struct sockaddr_storage
{
   sa_family_t ss_family;
   char        __ss_padding[26];
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
   short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};

struct timeval
{
   long tv_sec;
   long tv_usec;
};

struct fd_set
{
   fd_mask fd_bits;
};

#ifdef __cplusplus
extern "C" {
#endif

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
