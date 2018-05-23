#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>
#include <cstring>

#define SERVER_PORT 4405

int main(int argc, char **argv)
{
   struct sockaddr_in addr;
   unsigned short port = SERVER_PORT;

   if (argc == 2) {
      port = atoi(argv[1]);
   }

#ifdef _WIN32
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
      return -1;
   }
#endif

   // Create socket
   auto fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN32
   if (fd == INVALID_SOCKET) {
      WSACleanup();
#else
   if (fd < 0) {
#endif
      return -1;
   }

   // Set non blocking
#ifdef _WIN32
   u_long mode = 1;
   ioctlsocket(fd, FIONBIO, &mode);
#else
   int flags = fcntl(fd, F_GETFL, 0);
   fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#endif

   // Bind socket
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(port);
   if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
#ifdef _WIN32
      closesocket(fd);
      WSACleanup();
#else
      close(fd);
#endif
      return -1;
   }

   // Receive data
   char buffer[2048];
   bool running = true;

   while (running) {
      fd_set fdsRead;
      FD_ZERO(&fdsRead);
      FD_SET(fd, &fdsRead);

      struct timeval tv;
      tv.tv_sec = 0;
      tv.tv_usec = 10000;

      if (select(fd + 1, &fdsRead, NULL, NULL, &tv) == 1) {
         struct sockaddr_in from;
#ifdef _WIN32
         int fromLen = sizeof(from);
#else
         socklen_t fromLen = sizeof(from);
#endif
         int recvd = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &fromLen);

         if (recvd > 0) {
            buffer[recvd] = 0;
            std::cout << buffer;
            std::cout.flush();
         }
      }
   }

#ifdef _WIN32
   closesocket(fd);
   WSACleanup();
#else
   close(fd);
#endif
   return 0;
}
