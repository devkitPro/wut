#pragma once
#include <wut.h>

/**
 * \defgroup whb_hfio Host I/O access
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum WHBWellKnownHostDirectory
{
   //! A way to quickly reference the emulated MLC directory on a attached host
   //! pc.
   //!
   //! You should prefer to use this for compatability (as it will be the same
   //! across systems, even with separate paths), and it will usually be fewer
   //! characters meaning the actual path can be used by more of the important
   //! stuff.
   WHB_MLC_HOST_DIRECTORY           = 0,
   //! A way to quickly reference the emulated SLC directory on a attached host
   //! pc.
   //!
   //! You should prefer to use this for compatability (as it will be the same
   //! across systems, even with separate paths), and it will usually be fewer
   //! characters meaning the actual path can be used by more of the important
   //! stuff.
   WHB_SLC_HOST_DIRECTORY           = 1,
   //! A way to quickly reference the emulated directory of the 'optical disc'
   //! on a attached host pc.
   //!
   //! You should prefer to use this for compatability (as it will be the same
   //! across systems, even with separate paths), and it will usually be fewer
   //! characters meaning the actual path can be used by more of the important
   //! stuff.
   WHB_DISC_HOST_DIRECTORY          = 2,
   //! A way to quickly reference the emulated directory of the current titles
   //! save directory.
   //!
   //! You should prefer to use this for compatability (as it will be the same
   //! across systems, even with separate paths), and it will usually be fewer
   //! characters meaning the actual path can be used by more of the important
   //! stuff.
   WHB_SAVE_HOST_DIRECTORY          = 3,
   //! A way to quickly reference an attached network drive of the host pc.
   //!
   //! You should prefer to use this for compatability (as it will be the same
   //! across systems, even with separate paths), and it will usually be fewer
   //! characters meaning the actual path can be used by more of the important
   //! stuff.
   WHB_NETWORK_DRIVE_HOST_DIRECTORY = 4,
} WHBWellKnownHostDirectory;

BOOL
WHBMountHostFileIO();

char *
WHBGetHostFileIOMountPath();

char *
WHBPathForWellKnownHostDirectory(WHBWellKnownHostDirectory directory);

BOOL
WHBUnmountHostFileIO();

#ifdef __cplusplus
}
#endif

/** @} */
