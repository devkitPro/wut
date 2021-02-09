#pragma once
#include <stdint.h>
#include <sys/socket.h>

extern int h_errno;

struct hostent
{
   char  *h_name;
   char **h_aliases;
   int    h_addrtype;
   int    h_length;
   char **h_addr_list;
#define	h_addr h_addr_list[0]
};

struct servent
{
   char  *s_name;
   char **s_aliases;
   int    s_port;
   char  *s_proto;
};

struct addrinfo
{
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   socklen_t        ai_addrlen;
   char            *ai_canonname;
   struct sockaddr *ai_addr;
   struct addrinfo *ai_next;
};

#define NETDB_INTERNAL  -1
#define NETDB_SUCCESS   0
#define HOST_NOT_FOUND  1
#define TRY_AGAIN       2
#define NO_RECOVERY     3
#define NO_DATA         4
#define NO_ADDRESS      NO_DATA

#define EAI_ADDRFAMILY  1
#define EAI_AGAIN       2
#define EAI_BADFLAGS    3
#define EAI_FAIL        4
#define EAI_FAMILY      5
#define EAI_MEMORY      6
#define EAI_NODATA      7
#define EAI_NONAME      8
#define EAI_SERVICE     9
#define EAI_SOCKTYPE    10
#define EAI_SYSTEM      11
#define EAI_BADHINTS    12
#define EAI_PROTOCOL    13
#define EAI_OVERFLOW    14
#define EAI_MAX         15

#define NI_MAXHOST      1025
#define NI_MAXSERV      32

// nsysnet only implements NI_NOFQDN, NI_NUMERICHOST and NI_NUMERICSERV
#define NI_NOFQDN       0x0001
#define NI_NUMERICHOST  0x0002
#define NI_NAMEREQD     0x0004
#define NI_NUMERICSERV  0x0008
#define NI_DGRAM        0x0010
#define NI_NUMERICSCOPE 0x0020

// nsysnet only implements AI_PASSIVE, AI_CANONNAME and AI_NUMERICHOST
#define AI_PASSIVE      0x0001
#define AI_CANONNAME    0x0002
#define AI_NUMERICHOST  0x0004
#define AI_V4MAPPED     0x0008
#define AI_ALL          0x0010
#define AI_ADDRCONFIG   0x0020

#ifdef __cplusplus
extern "C" {
#endif

struct hostent *
gethostbyname(const char *name);

struct hostent *
gethostbyaddr(const void *addr,
              socklen_t len, 
              int type);

struct hostent *
gethostent(void);

struct servent *
getservbyname(const char *name,
              const char *proto);

struct servent *
getservbyport(int port,
              const char *proto);

struct servent *
getservent(void);

int
getaddrinfo(const char *node,
            const char *service,
            const struct addrinfo *hints,
            struct addrinfo **res);

void
freeaddrinfo(struct addrinfo *res);

int
getnameinfo(const struct sockaddr *addr,
            socklen_t addrlen,
            char *host,
            socklen_t hostlen,
            char *serv,
            socklen_t servlen,
            int flags);

const char *
gai_strerror(int ecode);

#ifdef __cplusplus
}
#endif
