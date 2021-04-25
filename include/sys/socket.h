#pragma once
#include <stdint.h>
#include <sys/time.h>

#define SOL_SOCKET      -1

#define PF_UNSPEC       0
#define PF_INET         2

#define AF_UNSPEC       PF_UNSPEC
#define AF_INET         PF_INET

#define SOCK_STREAM     1
#define SOCK_DGRAM      2

#define MSG_OOB         0x0001
#define MSG_PEEK        0x0002
#define MSG_DONTROUTE   0x0004
#define MSG_DONTWAIT    0x0020

#define SHUT_RD         0
#define SHUT_WR         1
#define SHUT_RDWR       2

/*
 * SOL_SOCKET options
 */
#define SO_REUSEADDR    0x0004      // reuse address
#define SO_KEEPALIVE    0x0008      // keep connections alive
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
#define SO_RXDATA       0x1011      // get count of bytes in sb_rcv
#define SO_TXDATA       0x1012      // get count of bytes in sb_snd
#define SO_NBIO         0x1014      // set socket to NON-blocking mode
#define SO_BIO          0x1015      // set socket to blocking mode
#define SO_NONBLOCK     0x1016      // set/get blocking mode via optval param

typedef uint32_t socklen_t;
typedef uint16_t sa_family_t;

struct sockaddr
{
   sa_family_t sa_family;
   char        sa_data[];
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

#ifdef __cplusplus
extern "C" {
#endif

// Wii U "extension"
void
socket_lib_init();

// Wii U "extension"
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

ssize_t
recv(int sockfd,
     void *buf,
     size_t len,
     int flags);

ssize_t
recvfrom(int sockfd,
         void *buf,
         size_t len,
         int flags,
         struct sockaddr *src_addr,
         socklen_t *addrlen);

ssize_t
send(int sockfd,
     const void *buf,
     size_t len,
     int flags);

ssize_t
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
sockatmark(int sockfd);

#ifdef __cplusplus
}
#endif

