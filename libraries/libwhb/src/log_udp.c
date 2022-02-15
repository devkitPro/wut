#include <coreinit/memdefaultheap.h>
#include <coreinit/mutex.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/libmanager.h>

static int
sSocket = -1;

static struct sockaddr_in
sSendAddr;

#define SERVER_PORT 4405

static void
udpLogHandler(const char *msg)
{
   sendto(sSocket,
          msg,
          strlen(msg),
          0,
          (struct sockaddr *)&sSendAddr,
          sizeof(struct sockaddr_in));
}

BOOL
WHBLogUdpInit()
{
   int broadcastEnable = 1;

   sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (sSocket < 0) {
      return FALSE;
   }

   setsockopt(sSocket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

   memset(&sSendAddr, 0, sizeof(struct sockaddr_in));
   sSendAddr.sin_family = AF_INET;
   sSendAddr.sin_port = htons(SERVER_PORT);
   sSendAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

   return WHBAddLogHandler(udpLogHandler);
}

BOOL
WHBLogUdpDeinit()
{
   shutdown(sSocket, SHUT_WR);
   close(sSocket);
   sSocket = -1;

   return WHBRemoveLogHandler(udpLogHandler);
}
