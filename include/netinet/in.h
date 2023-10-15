#pragma once
#include <stdint.h>
#include <sys/socket.h>

#define INADDR_ANY         0x00000000
#define INADDR_LOOPBACK    0x7F000001
#define INADDR_BROADCAST   0xFFFFFFFF
#define INADDR_NONE        0xFFFFFFFF

#define INET_ADDRSTRLEN    16

#define IPPROTO_IP         0
#define IPPROTO_TCP        6
#define IPPROTO_UDP        17

#define IP_TOS             3
#define IP_TTL             4
#define IP_MULTICAST_IF    9
#define IP_MULTICAST_TTL   10
#define IP_MULTICAST_LOOP  11
#define IP_ADD_MEMBERSHIP  12
#define IP_DROP_MEMBERSHIP 13
#define IP_UNKNOWN         14

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;

struct in_addr
{
   in_addr_t       s_addr;
};

struct sockaddr_in
{
   sa_family_t     sin_family;
   in_port_t       sin_port;
   struct in_addr  sin_addr;
   unsigned char   sin_zero[8];
};

struct ip_mreq
{
   struct in_addr imr_multiaddr;
   struct in_addr imr_interface;
};
