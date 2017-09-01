#pragma once

/**
 * \defgroup whb_commandserver Network Command Server
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define WHB_SERVER_BUFFER_SIZE 1024

BOOL
WHBCommandServerInit();

void
WHBCommandServerStop();

BOOL
WHBCommandServerListen(char * stringLocation);

#ifdef __cplusplus
}
#endif

/** @} */
