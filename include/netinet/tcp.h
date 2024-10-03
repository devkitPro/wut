#pragma once

#define SOL_TCP          6

#define TCP_ACKDELAYTIME 0x2001
#define TCP_NOACKDELAY   0x2002
#define TCP_MAXSEG       0x2003
#define TCP_NODELAY      0x2004
#define TCP_UNKNOWN      0x2005 // amount of mss received before sending an ack
