#pragma once

/**
 * \defgroup whb_socketinit Socket Library Initialization Manager
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Socket Library (nsysnet.rpl)
 */

__attribute__ ((deprecated)) void
WHBInitializeSocketLibrary();

__attribute__ ((deprecated)) void
WHBDeinitializeSocketLibrary();

#ifdef __cplusplus
}
#endif

/** @} */
