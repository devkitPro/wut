#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_ios IOS
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOSVec IOSVec;
typedef int32_t IOSHandle;

typedef enum IOSOpenMode
{
   IOS_OPEN_READ        = 1 << 0,
   IOS_OPEN_WRITE       = 1 << 1,
   IOS_OPEN_READWRITE   = IOS_OPEN_READ | IOS_OPEN_WRITE,
} IOSOpenMode;

typedef enum IOSError
{
   IOS_ERROR_OK                  = 0,
   IOS_ERROR_ACCESS              = -1,
   IOS_ERROR_EXISTS              = -2,
   IOS_ERROR_INTR                = -3,
   IOS_ERROR_INVALID             = -4,
   IOS_ERROR_MAX                 = -5,
   IOS_ERROR_NOEXISTS            = -6,
   IOS_ERROR_QEMPTY              = -7,
   IOS_ERROR_QFULL               = -8,
   IOS_ERROR_UNKNOWN             = -9,
   IOS_ERROR_NOTREADY            = -10,
   IOS_ERROR_ECC                 = -11,
   IOS_ERROR_ECCCRIT             = -12,
   IOS_ERROR_BADBLOCK            = -13,
   IOS_ERROR_INVALIDOBJTYPE      = -14,
   IOS_ERROR_INVALIDRNG          = -15,
   IOS_ERROR_INVALIDFLAG         = -16,
   IOS_ERROR_INVALIDFORMAT       = -17,
   IOS_ERROR_INVALIDVERSION      = -18,
   IOS_ERROR_INVALIDSIGNER       = -19,
   IOS_ERROR_FAILCHECKVALUE      = -20,
   IOS_ERROR_FAILINTERNAL        = -21,
   IOS_ERROR_FAILALLOC           = -22,
   IOS_ERROR_INVALIDSIZE         = -23,
   IOS_ERROR_NOLINK              = -24,
   IOS_ERROR_ANFAILED            = -25,
   IOS_ERROR_MAXSEMCOUNT         = -26,
   IOS_ERROR_SEMUNAVAILABLE      = -27,
   IOS_ERROR_INVALIDHANDLE       = -28,
   IOS_ERROR_INVALIDARG          = -29,
   IOS_ERROR_NORESOURCE          = -30,
   IOS_ERROR_BUSY                = -31,
   IOS_ERROR_TIMEOUT             = -32,
   IOS_ERROR_ALIGNMENT           = -33,
   IOS_ERROR_BSP                 = -34,
   IOS_ERROR_DATAPENDING         = -35,
   IOS_ERROR_EXPIRED             = -36,
   IOS_ERROR_NOREADACCESS        = -37,
   IOS_ERROR_NOWRITEACCESS       = -38,
   IOS_ERROR_NOREADWRITEACCESS   = -39,
   IOS_ERROR_CLIENTTXNLIMIT      = -40,
   IOS_ERROR_STALEHANDLE         = -41,
   IOS_ERROR_UNKNOWNVALUE        = -42,
} IOSError;

struct IOSVec
{
   //! Virtual address of buffer.
   void *vaddr;

   //! Length of buffer.
   uint32_t len;

   //! Physical address of buffer.
   void *paddr;
};
WUT_CHECK_OFFSET(IOSVec, 0x00, vaddr);
WUT_CHECK_OFFSET(IOSVec, 0x04, len);
WUT_CHECK_OFFSET(IOSVec, 0x08, paddr);
WUT_CHECK_SIZE(IOSVec, 0x0C);

typedef void (*IOSAsyncCallbackFn)(IOSError, void *);

IOSError
IOS_Open(const char *device,
         IOSOpenMode mode);

IOSError
IOS_OpenAsync(const char *device,
              IOSOpenMode mode,
              IOSAsyncCallbackFn callback,
              void *context);

IOSError
IOS_Close(IOSHandle handle);

IOSError
IOS_CloseAsync(IOSHandle handle,
               IOSAsyncCallbackFn callback,
               void *context);

IOSError
IOS_Ioctl(IOSHandle handle,
          uint32_t request,
          void *inBuf,
          uint32_t inLen,
          void *outBuf,
          uint32_t outLen);

IOSError
IOS_IoctlAsync(IOSHandle handle,
               uint32_t request,
               void *inBuf,
               uint32_t inLen,
               void *outBuf,
               uint32_t outLen,
               IOSAsyncCallbackFn callback,
               void *context);

IOSError
IOS_Ioctlv(IOSHandle handle,
           uint32_t request,
           uint32_t vecIn,
           uint32_t vecOut,
           IOSVec *vec);

IOSError
IOS_IoctlvAsync(IOSHandle handle,
                uint32_t request,
                uint32_t vecIn,
                uint32_t vecOut,
                IOSVec *vec,
                IOSAsyncCallbackFn callback,
                void *context);

#ifdef __cplusplus
}
#endif

/** @} */
