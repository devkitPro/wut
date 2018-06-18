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

typedef int32_t NSSLContextHandle;
typedef int32_t NSSLConnectionHandle;

typedef enum NSSLServerCertId
{
    NSSL_SERVER_CERT_GROUP_0_FIRST  = 100,
    NSSL_SERVER_CERT_GROUP_0_LAST   = 105,

    NSSL_SERVER_CERT_GROUP_1_FIRST  = 1001,
    NSSL_SERVER_CERT_GROUP_1_LAST   = 1033,
} NSSLServerCertId;

int32_t
NSSLInit();

int32_t
NSSLFinish();

NSSLContextHandle
NSSLCreateContext(int32_t unk);

int32_t
NSSLDestroyContext(NSSLContextHandle context);

int32_t
NSSLAddServerPKIExternal(NSSLContextHandle context,
                         const void *cert,
                         int32_t length,
                         int32_t unk);

int32_t
NSSLAddServerPKI(NSSLContextHandle context,
                 NSSLServerCertId pki);

NSSLConnectionHandle
NSSLCreateConnection(NSSLContextHandle context,
                     const char *host,
                     int32_t hostLength,
                     int32_t options,
                     int32_t socket,
                     int32_t block);

int32_t
NSSLRead(NSSLConnectionHandle connection,
         const void *buffer,
         int32_t length,
         int32_t *outBytesRead);

int32_t
NSSLWrite(NSSLConnectionHandle connection,
          const void *buffer,
          int32_t length,
          int32_t *outBytesWritten);

#ifdef __cplusplus
}
#endif

/** @} */
