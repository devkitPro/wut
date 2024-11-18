#pragma once
#include <wut.h>
#include <netdb.h>

/**
 * \defgroup nsysnet_netdb Netdb
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

struct hostent *
RPLWRAP(gethostbyaddr)(const void *addr,
                       size_t len, 
                       int type);

struct hostent *
RPLWRAP(gethostbyname)(const char *name);

int
RPLWRAP(getaddrinfo)(const char *node,
                     const char *service,
                     const struct addrinfo *hints,
                     struct addrinfo **res);

void
RPLWRAP(freeaddrinfo)(struct addrinfo *res);

int
RPLWRAP(getnameinfo)(const struct sockaddr *addr,
                     socklen_t addrlen,
                     char *host,
                     socklen_t hostlen,
                     char *serv,
                     socklen_t servlen,
                     int flags);

void 
RPLWRAP(clear_resolver_cache)(void);

int
RPLWRAP(set_resolver_allocator)(void* (*alloc)(uint32_t),
                                void (*free)(void*));

int *
RPLWRAP(get_h_errno)(void);

const char *
RPLWRAP(gai_strerror)(int ecode);

// clang-format on

#ifdef __cplusplus
}
#endif

/** @} */
