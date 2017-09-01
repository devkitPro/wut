#include <coreinit/baseheap.h>
#include <coreinit/expandedheap.h>
#include <nsysnet/socket.h>
#include <whb/commandserver.h>
#include <whb/libmanager.h>
#include <whb/log.h>

#include <string.h>

#define SERVER_PORT 4406

int
sSocket = -1;

struct sockaddr_in
sAddr;

void
closeSocket(const char * funcName)
{
   int ret = socketclose(sSocket);
   if(ret < 0) {
      WHBLogPrintf("%s: Error occurred closing socket: %d", funcName, socketlasterr());
   }
}

void
closeClient(const char * funcName, int fd)
{
   int ret = socketclose(fd);
   if(ret < 0) {
      WHBLogPrintf("%s: Error occurred closing client socket: %d", funcName, socketlasterr());
   }
}

BOOL
WHBCommandServerInit()
{
   int ret = 0;

   if(sSocket >= 0) {
      WHBLogPrintf("%s: Command server is already running.", __FUNCTION__);
      return TRUE;
   }

   WHBInitializeSocketLibrary();

   sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(sSocket < 0) {
      WHBLogPrintf("%s: Error occurred while creating socket: %d", __FUNCTION__, socketlasterr());
      sSocket = -1;
      return FALSE;
   }

   memset(&sAddr, 0, sizeof(struct sockaddr_in));
   sAddr.sin_family = AF_INET;
   sAddr.sin_port = htons(SERVER_PORT);
   sAddr.sin_addr.s_addr = htonl(INADDR_ANY);

   ret = bind(sSocket, (struct sockaddr *)&sAddr, sizeof(struct sockaddr_in));
   if(ret < 0) {
      WHBLogPrintf("%s: Error occurred while binding to socket: %d", __FUNCTION__, socketlasterr());
      closeSocket(__FUNCTION__);
      sSocket = -1;
      return FALSE;
   }

   ret = listen(sSocket, 3);
   if(ret < 0) {
      WHBLogPrintf("%s: Error occurred while setting socket to listen mode: %d", __FUNCTION__, socketlasterr());
      closeSocket(__FUNCTION__);
      sSocket = -1;
      return FALSE;
   }

   return TRUE;
}

void
WHBCommandServerStop()
{
   if(sSocket < 0) {
      WHBLogPrintf("%s: Socket is already closed.", __FUNCTION__);
      return;
   }

   closeSocket(__FUNCTION__);
   sSocket = -1;
   WHBDeinitializeSocketLibrary();
}

BOOL
WHBCommandServerListen(char * stringLocation)
{
   char buffer[WHB_SERVER_BUFFER_SIZE];
   memset(buffer, 0, WHB_SERVER_BUFFER_SIZE);

   int ret, sClient;
   struct sockaddr_in sClientAddr;
   socklen_t sClientAddrLen = sizeof(struct sockaddr_in);

   if(sSocket < 0) {
      WHBLogPrintf("%s: Socket is not open. Please run WHBCommandServerInit() first.", __FUNCTION__);
      return FALSE;
   }

   sClient = accept(sSocket, (struct sockaddr *)&sClientAddr, &sClientAddrLen);
   if(sClient < 0) {
      WHBLogPrintf("%s: Error occurred while accepting a client connection: %d", __FUNCTION__, socketlasterr());
      return FALSE;
   }

   ret = recv(sClient, buffer, WHB_SERVER_BUFFER_SIZE, 0);
   if(ret < 0) {
      WHBLogPrintf("%s: Error occurred while receiving data from client: %d", __FUNCTION__, socketlasterr());
      closeClient(__FUNCTION__, sClient);
      return FALSE;
   }

   closeClient(__FUNCTION__, sClient);
   memcpy(stringLocation, buffer, WHB_SERVER_BUFFER_SIZE);
   return TRUE;
}
