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

void
WHBInitializeSocketLibrary();

void
WHBDeinitializeSocketLibrary();

#ifdef __cplusplus
}
#endif

/** @} */
