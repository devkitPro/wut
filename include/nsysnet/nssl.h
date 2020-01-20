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
 * For HTTPS connections, consider using nlibcurl.
 *
 * \if false
 * meta: how to link to nlibcurl's Doxygen page?
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
 *
 * The names and fingerprints given in this documentation are taken from the
 * real certificates inside the Wii U's CDN package.
 *
 * \if false
 * Certificate list taken from 0005001B-10054000/content/certstore_metadata.txt
 * \endif
 */
typedef enum NSSLServerCertId
{
    //! Represents the first certificate in the Nintendo CA group.
    NSSL_SERVER_CERT_GROUP_NINTENDO_FIRST  = 100,
    //! Nintendo CA
    //! (SHA1: B5 22 94 55 DD 26 C1 F5 3C 73 06 0E 90 89 B3 91 38 9E 1F 75)
    NSSL_SERVER_CERT_NINTENDO_CA = 100,
    //! Nintendo CA - G2
    //! (SHA1: C6 0B 2A 5C C9 0F 06 30 CC A3 30 40 DF 6B 33 78 23 9F 3B FA)
    NSSL_SERVER_CERT_NINTENDO_CA_G2 = 101,
    //! Nintendo CA - G3
    //! (SHA1: 68 A0 77 05 CC C7 A4 08 41 6E 0E D7 AD 65 F2 EC 3F EA 98 62)
    NSSL_SERVER_CERT_NINTENDO_CA_G3 = 102,
    //! Nintendo Class 2 CA
    //! (SHA1: AA 8E F6 6A E0 F8 07 ED B8 41 C8 89 EE 36 66 A2 59 A2 8C CC)
    NSSL_SERVER_CERT_NINTENDO_CLASS2_CA = 103,
    //! Nintendo Class 2 CA - G2
    //! (SHA1: 03 9D E5 37 3A C6 5E 1A EE 89 8D 54 E7 56 35 76 EB BE 54 9B)
    NSSL_SERVER_CERT_NINTENDO_CLASS2_CA_G2 = 104,
    //! Nintendo Class 2 CA - G3
    //! (SHA1: FA B5 6C 4C C7 CF F5 07 1D 40 B6 B0 07 38 61 D2 90 CA 2A 1A)
    NSSL_SERVER_CERT_NINTENDO_CLASS2_CA_G3 = 105,
    //! Represents the last certificate in the Nintendo CA group.
    NSSL_SERVER_CERT_GROUP_NINTENDO_LAST   = 105,

    //! Represents the first certificate in the commercial CA group.
    NSSL_SERVER_CERT_GROUP_COMMERCIAL_FIRST  = 1001,
    //! Baltimore CyberTrust Root
    //! (SHA1: D4 DE 20 D0 5E 66 FC 53 FE 1A 50 88 2C 78 DB 28 52 CA E4 74)
    NSSL_SERVER_CERT_BALTIMORE_CYBERTRUST_ROOT_CA = 1001,
    //! Cybertrust Global Root
    //! (SHA1: 5F 43 E5 B1 BF F8 78 8C AC 1C C7 CA 4A 9A C6 22 2B CC 34 C6)
    NSSL_SERVER_CERT_CYBERTRUST_GLOBAL_ROOT_CA = 1002,
    //! Verizon Global Root
    //! (SHA1: 91 21 98 EE F2 3D CA C4 09 39 31 2F EE 97 DD 56 0B AE 49 B1)
    NSSL_SERVER_CERT_VERIZON_GLOBAL_ROOT_CA = 1003,
    //! GlobalSign Root CA
    //! (SHA1: B1 BC 96 8B D4 F4 9D 62 2A A8 9A 81 F2 15 01 52 A4 1D 82 9C)
    NSSL_SERVER_CERT_GLOBALSIGN_ROOT_CA = 1004,
    //! GlobalSign
    //! (SHA1: 75 E0 AB B6 13 85 12 27 1C 04 F8 5F DD DE 38 E4 B7 24 2E FE)
    NSSL_SERVER_CERT_GLOBALSIGN_ROOT_CA_R2 = 1005,
    //! GlobalSign
    //! (SHA1: D6 9B 56 11 48 F0 1C 77 C5 45 78 C1 09 26 DF 5B 85 69 76 AD)
    NSSL_SERVER_CERT_GLOBALSIGN_ROOT_CA_R3 = 1006,
    //! VeriSign Class 3 Public Primary Certification Authority - G3
    //! (SHA1: 13 2D 0D 45 53 4B 69 97 CD B2 D5 C3 39 E2 55 76 60 9B 5C C6)
    NSSL_SERVER_CERT_VERISIGN_CLASS3_PUBLIC_PRIMARY_CA_G3 = 1007,
    //! VeriSign Universal Root Certification Authority
    //! (SHA1: 36 79 CA 35 66 87 72 30 4D 30 A5 FB 87 3B 0F A7 7B B7 0D 54)
    NSSL_SERVER_CERT_VERISIGN_UNIVERSAL_ROOT_CA = 1008,
    //! VeriSign Class 3 Public Primary Certification Authority - G5
    //! (SHA1: 4E B6 D5 78 49 9B 1C CF 5F 58 1E AD 56 BE 3D 9B 67 44 A5 E5)
    NSSL_SERVER_CERT_VERISIGN_CLASS3_PUBLIC_PRIMARY_CA_G5 = 1009,
    //! thawte Primary Root CA - G3
    //! (SHA1: F1 8B 53 8D 1B E9 03 B6 A6 F0 56 43 5B 17 15 89 CA F3 6B F2)
    NSSL_SERVER_CERT_THAWTE_PRIMARY_ROOT_CA_G3 = 1010,
    //! thawte Primary Root CA
    //! (SHA1: 91 C6 D6 EE 3E 8A C8 63 84 E5 48 C2 99 29 5C 75 6C 81 7B 81)
    NSSL_SERVER_CERT_THAWTE_PRIMARY_ROOT_CA = 1011,
    //! GeoTrust Global CA
    //! (SHA1: DE 28 F4 A4 FF E5 B9 2F A3 C5 03 D1 A3 49 A7 F9 96 2A 82 12)
    NSSL_SERVER_CERT_GEOTRUST_GLOBAL_CA = 1012,
    //! GeoTrust Global CA 2
    //! (SHA1: A9 E9 78 08 14 37 58 88 F2 05 19 B0 6D 2B 0D 2B 60 16 90 7D)
    NSSL_SERVER_CERT_GEOTRUST_GLOBAL_CA2 = 1013,
    //! GeoTrust Primary Certification Authority
    //! (SHA1: 32 3C 11 8E 1B F7 B8 B6 52 54 E2 E2 10 0D D6 02 90 37 F0 96)
    NSSL_SERVER_CERT_GEOTRUST_PRIMARY_CA = 1014,
    //! GeoTrust Primary Certification Authority - G3
    //! (SHA1: 03 9E ED B8 0B E7 A0 3C 69 53 89 3B 20 D2 D9 32 3A 4C 2A FD)
    NSSL_SERVER_CERT_GEOTRUST_PRIMARY_CA_G3 = 1015,
    //! AddTrust External CA Root
    //! (SHA1: 02 FA F3 E2 91 43 54 68 60 78 57 69 4D F5 E4 5B 68 85 18 68)
    NSSL_SERVER_CERT_ADDTRUST_EXT_CA_ROOT = 1016,
    //! COMODO Certification Authority
    //! (SHA1: EE 86 93 87 FF FD 83 49 AB 5A D1 43 22 58 87 89 A4 57 B0 12)
    NSSL_SERVER_CERT_COMODO_CA = 1017,
    //! UTN - DATACorp SGC
    //! (SHA1: 58 11 9F 0E 12 82 87 EA 50 FD D9 87 45 6F 4F 78 DC FA D6 D4)
    NSSL_SERVER_CERT_UTN_DATACORP_SGC_CA = 1018,
    //! UTN-USERFirst-Hardware
    //! (SHA1: 04 83 ED 33 99 AC 36 08 05 87 22 ED BC 5E 46 00 E3 BE F9 D7)
    NSSL_SERVER_CERT_UTN_USERFIRST_HARDWARE_CA = 1019,
    //! DigiCert High Assurance EV Root CA
    //! (SHA1: 5F B7 EE 06 33 E2 59 DB AD 0C 4C 9A E6 D3 8F 1A 61 C7 DC 25)
    NSSL_SERVER_CERT_DIGICERT_HIGH_ASSURANCE_EV_ROOT_CA = 1020,
    //! DigiCert Assured ID Root CA
    //! (SHA1: 05 63 B8 63 0D 62 D7 5A BB C8 AB 1E 4B DF B5 A8 99 B2 4D 43)
    NSSL_SERVER_CERT_DIGICERT_ASSURED_ID_ROOT_CA = 1021,
    //! DigiCert Global Root CA
    //! (SHA1: A8 98 5D 3A 65 E5 E5 C4 B2 D7 D6 6D 40 C6 DD 2F B1 9C 54 36)
    NSSL_SERVER_CERT_DIGICERT_GLOBAL_ROOT_CA = 1022,
    //! GTE CyberTrust Global Root
    //! (SHA1: 97 81 79 50 D8 1C 96 70 CC 34 D8 09 CF 79 44 31 36 7E F4 74)
    NSSL_SERVER_CERT_GTE_CYBERTRUST_GLOBAL_ROOT = 1023,
    //! [No common name]
    //! (SHA1: A1 DB 63 93 91 6F 17 E4 18 55 09 40 04 15 C7 02 40 B0 AE 6B)
    NSSL_SERVER_CERT_VERISIGN_CLASS3_PUBLIC_PRIMARY_CA = 1024,
    //! Thawte Premium Server CA
    //! (SHA1: 62 7F 8D 78 27 65 63 99 D2 7D 7F 90 44 C9 FE B3 F3 3E FA 9A)
    NSSL_SERVER_CERT_THAWTE_PREMIUM_SERVER_CA = 1025,
    //! [No common name]
    //! (SHA1: D2 32 09 AD 23 D3 14 23 21 74 E4 0D 7F 9D 62 13 97 86 63 3A)
    NSSL_SERVER_CERT_EQUIFAX_SECURE_CA = 1026,
    //! Entrust.net Secure Server Certification Authority
    //! (SHA1: 99 A6 9B E6 1A FE 88 6B 4D 2B 82 00 7C B8 54 FC 31 7E 15 39)
    NSSL_SERVER_CERT_ENTRUST_SECURE_SERVER_CA = 1027,
    //! [No common name]
    //! (SHA1: 85 37 1C A6 E5 50 14 3D CE 28 03 47 1B DE 3A 09 E8 F8 77 0F)
    NSSL_SERVER_CERT_VERISIGN_CLASS3_PUBLIC_PRIMARY_CA_G2 = 1028,
    //! Entrust.net Certification Authority (2048)
    //! (SHA1: 50 30 06 09 1D 97 D4 F5 AE 39 F7 CB E7 92 7D 7D 65 2D 34 31)
    NSSL_SERVER_CERT_ENTRUST_CA_2048 = 1029,
    //! Entrust Root Certification Authority
    //! (SHA1: B3 1E B1 B7 40 E3 6C 84 02 DA DC 37 D4 4D F5 D4 67 49 52 F9)
    NSSL_SERVER_CERT_ENTRUST_ROOT_CA = 1030,
    //! Entrust Root Certification Authority - G2
    //! (SHA1: 8C F4 27 FD 79 0C 3A D1 66 06 8D E8 1E 57 EF BB 93 22 72 D4)
    NSSL_SERVER_CERT_ENTRUST_ROOT_CA_G2 = 1031,
    //! DigiCert Assured ID Root G2
    //! (SHA1: A1 4B 48 D9 43 EE 0A 0E 40 90 4F 3C E0 A4 C0 91 93 51 5D 3F)
    NSSL_SERVER_CERT_DIGICERT_ASSURED_ID_ROOT_CA_G2 = 1032,
    //! DigiCert Global Root G2
    //! (SHA1: DF 3C 24 F9 BF D6 66 76 1B 26 80 73 FE 06 D1 CC 8D 4F 82 A4)
    NSSL_SERVER_CERT_DIGICERT_GLOBAL_ROOT_CA_G2 = 1033,
    //! Represents the last certificate in the commerical CA group.
    NSSL_SERVER_CERT_GROUP_COMMERCIAL_LAST   = 1033,

    //! Represents the first certificate in the 4096-bit commercial CA group.
    NSSL_SERVER_CERT_GROUP_COMMERCIAL_4096_FIRST = 1900,
    //! COMODO RSA Certification Authority
    //! (SHA1: AF E5 D2 44 A8 D1 19 42 30 FF 47 9F E2 F8 97 BB CD 7A 8C B4)
    NSSL_SERVER_CERT_COMODO_RSA_CA = 1900,
    //! USERTrust RSA Certification Authority
    //! (SHA1: 2B 8F 1B 57 33 0D BB A2 D0 7A 6C 51 F7 0E E9 0D DA B9 AD 8E)
    NSSL_SERVER_CERT_USERTRUST_RSA_CA = 1901,
    //! Represents the last certificate in the 4096-bit commercial CA group.
    NSSL_SERVER_CERT_GROUP_COMMERCIAL_4096_LAST = 1901,
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
 * 0 on success, or a negative value if an error occurred.
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
 * If opening a new underlying socket, whether to open it in blocking mode.
 *
 * \returns
 * A #NSSLConnectionHandle representing the current connection.
 *
 * \sa
 * - NSSLRead()
 * - NSSLWrite()
 * - NSSLDestroyConnection()
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
 * Close and destroy a NSSL connection.
 *
 * \param connection
 * The connection to destroy.
 *
 * \returns
 * 0 on success or a negative error value.
 */
int32_t
NSSLDestroyConnection(NSSLConnectionHandle connection);

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
