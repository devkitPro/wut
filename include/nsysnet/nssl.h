#pragma once
#include <wut.h>

/**
 * \defgroup nsysnet_nssl Nintendo SSL
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef void *NSSLContext;
typedef void *NSSLConnection;

int32_t
NSSLInit();

int32_t
NSSLFinish();

NSSLContext
NSSLCreateContext(int32_t unk);

int32_t
NSSLDestroyContext(NSSLContext context);

int32_t
NSSLAddServerPKIExternal(NSSLContext context,
                         const void *cert,
                         int32_t length,
                         int32_t unk);

int32_t
NSSLAddServerPKI(NSSLContext context,
                 int32_t pki);

NSSLConnection
NSSLCreateConnection(NSSLContext context,
                     const char *host,
                     int32_t hostLength,
                     int32_t options,
                     int32_t socket,
                     int32_t block);

int32_t
NSSLRead(NSSLConnection connection,
         const void *buffer,
         int32_t length,
         int32_t *outBytesRead);

int32_t
NSSLWrite(NSSLConnection connection,
          const void *buffer,
          int32_t length,
          int32_t *outBytesWritten);

#ifdef __cplusplus
}
#endif

/** @} */
