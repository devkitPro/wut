#pragma once
#include <wut.h>

/**
 * \defgroup nsysnet_nssl Nintendo SSL
 * \ingroup nsysnet
 *
 * The NSSL library is Nintendo's interface for making SSL connections on the
 * Wii U. To use NSSL directly, call NSSLInit() then NSSLCreateContext() to
 * create a context. This context - after adding root CAs via NSSLAddServerPKI()
 * or NSSLAddServerPKIExternal() - can be used to create connections
 * (NSSLCreateConnection()) that can transfer data using NSSLRead() and
 * NSSLWrite().
 *
 * For HTTPS connections, consider using libcurl.
 *
 * \if false
 * meta: how to link to libcurl?
 * \endif
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

//! A handle to a NSSL context created with NSSLCreateContext().
typedef int32_t NSSLContextHandle;
//! A handle to a NSSL connection created with NSSLCreateConnection().
typedef int32_t NSSLConnectionHandle;

/**
 * The IDs of a system CA. These certificates are built-in to the system and can
 * be added to a NSSL context with NSSLAddServerPKI().
 */
typedef enum NSSLServerCertId
{
    //! Represents the first certificate in the Nintendo CA group.
    NSSL_SERVER_CERT_GROUP_0_FIRST  = 100,
    //! Represents the last certificate in the Nintendo CA group.
    NSSL_SERVER_CERT_GROUP_0_LAST   = 105,

    //! Represents the first certificate in the commercial CA group.
    NSSL_SERVER_CERT_GROUP_1_FIRST  = 1001,
    //! Represents the last certificate in the commerical CA group.
    NSSL_SERVER_CERT_GROUP_1_LAST   = 1033,
} NSSLServerCertId;

/**
 * Initialises the NSSL library for use. This must be called before any other
 * NSSL functions.
 *
 * \returns
 * 0 on success, or a negative error code on failure.
 *
 * \sa
 * - NSSLFinish()
 */
int32_t
NSSLInit();

/**
 * Cleans up and finishes use of the NSSL library.
 *
 * \returns
 * 0 on success, or -1 on error.
 */
int32_t
NSSLFinish();

/**
 * Creates a context to use with the NSSL library. A context contains root CAs
 * and connections.
 *
 * \param unk
 * Unknown. A value of 0 appears to work.
 *
 * \returns
 * A #NSSLContextHandle representing the newly created context, or a negative
 * value on error.
 *
 * \sa
 * - NSSLDestroyContext()
 */
NSSLContextHandle
NSSLCreateContext(int32_t unk);

/**
 * Destroys a NSSL context.
 *
 * \param context
 * The NSSL context to destroy.
 *
 * \returns
 * 0 on success, or a negative value if an error occured.
 */
int32_t
NSSLDestroyContext(NSSLContextHandle context);

/**
 * Add a custom root CA to the given NSSL context.
 *
 * \param context
 * The NSSL context to add a root CA to.
 *
 * \param cert
 * A pointer to a buffer containing the certificate data.
 *
 * \param length
 * The length of the certificate buffer.
 *
 * \param unk
 * Unknown.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - NSSLAddServerPKI()
 *
 * \if false
 * meta: what format does the certificate need to be? The internal ones are
 * x509 in binary DER. What's a working value for unk? 0?
 * \endif
 */
int32_t
NSSLAddServerPKIExternal(NSSLContextHandle context,
                         const void *cert,
                         int32_t length,
                         int32_t unk);

/**
 * Add a system root CA (one of #NSSLServerCertId) to the given NSSL context.
 *
 * \param context
 * The NSSL context to add a root CA to.
 *
 * \param pki
 * The #NSSLServerCertId representing the system CA to add.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - NSSLAddServerPKIExternal()
 */
int32_t
NSSLAddServerPKI(NSSLContextHandle context,
                 NSSLServerCertId pki);

/**
 * Open an SSL connection.
 *
 * \param context
 * The context to open the connection under.
 *
 * \param host
 * The domain or IP of the host to connect to.
 *
 * \param hostLength
 * The length of the "host" buffer.
 *
 * \param options
 * Options for the underlying socket.
 *
 * \param socket
 * An existing socket to use for the connection, or NULL.
 *
 * \param block
 * Whether to block until the connection is open.
 *
 * \returns
 * A #NSSLConnectionHandle representing the current connection.
 *
 * \sa
 * - NSSLRead()
 * - NSSLWrite()
 *
 * \if false
 * meta: kinda guessing socket and options here, needs confirmation
 * \endif
 */
NSSLConnectionHandle
NSSLCreateConnection(NSSLContextHandle context,
                     const char *host,
                     int32_t hostLength,
                     int32_t options,
                     int32_t socket,
                     int32_t block);

/**
 * Read data from an open NSSL connection into a given buffer.
 *
 * \param connection
 * The connection to read data from.
 *
 * \param buffer
 * A buffer to read decrypted data into.
 *
 * \param length
 * The length of the given buffer.
 *
 * \param outBytesRead
 * A pointer to write the actual number of read bytes into. This may be smaller
 * than the input buffer.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - NSSLWrite()
 */
int32_t
NSSLRead(NSSLConnectionHandle connection,
         const void *buffer,
         int32_t length,
         int32_t *outBytesRead);

/**
 * Write data to an open NSSL connection from a given buffer.
 *
 * \param connection
 * The connection to write data to.
 *
 * \param buffer
 * A buffer containing the data to be sent.
 *
 * \param length
 * The length of the given buffer.
 *
 * \param outBytesWritten
 * A pointer to write the actual number of written bytes into. This may be
 * smaller than the input buffer.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - NSSLRead()
 */
int32_t
NSSLWrite(NSSLConnectionHandle connection,
          const void *buffer,
          int32_t length,
          int32_t *outBytesWritten);

#ifdef __cplusplus
}
#endif

/** @} */
