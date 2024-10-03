#pragma once
#include <wut.h>

/**
 * \defgroup nn_nets2_somemopt
 * \ingroup nn_nets2
 * User provided socket memory options.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SOMemOptRequest
{
   //! Initialize buffer managment from user-provided buffer.
   //! This is a blocking request, which only returns once nsysnet is shut down/the application quits.
   SOMEMOPT_REQUEST_INIT           = 1,
   //! Return the amount of bytes used for buffer management.
   SOMEMOPT_REQUEST_GET_BYTES_USED = 2,
   //! Wait for buffer management initialization to be done.
   SOMEMOPT_REQUEST_WAIT_FOR_INIT  = 3,
   //! Cancel pending wait for init.
   SOMEMOPT_REQUEST_CANCEL_WAIT    = 4,
} SOMemOptRequest;

typedef enum SOMemOptFlags
{
   SOMEMOPT_FLAGS_NONE        = 0,
   //! Changes the distribution between small and big buffers to 50-50 instead of 80-20.
   SOMEMOPT_FLAGS_BIG_BUFFERS = 1 << 0,
} SOMemOptFlags;

/**
 * Perform a somemopt request.
 * 
 * \param request
 * The request to perform.
 * 
 * \param buffer
 * A 0x40 aligned buffer for \link SOMEMOPT_REQUEST_INIT \endlink.
 * 
 * \param size
 * The size of the buffer for \link SOMEMOPT_REQUEST_INIT \endlink.
 * Minimum size is \c 0x20000 bytes, maximum size is \c 0x300000.
 * 
 * \param flags
 * A combination of flags.
 * 
 * \return
 * -1 on error.
 */
int
somemopt(SOMemOptRequest request,
         void *buffer,
         uint32_t size,
         SOMemOptFlags flags);

// clang-format off
int
RPLWRAP(somemopt)(SOMemOptRequest request,
                  void *buffer,
                  uint32_t size,
                  SOMemOptFlags flags);
// clang-format on

#ifdef __cplusplus
}
#endif
