#pragma once
#include <wut.h>

/**
 * \defgroup whb_file Filesystem
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum WHBFileError
{
   WHB_FILE_OK = 0,
   WHB_FILE_FATAL_ERROR = -1,
} WHBFileError;

int32_t
WHBOpenFile(const char *path,
            const char *mode);

uint32_t
WHBGetFileSize(int32_t handle);

uint32_t
WHBReadFile(int32_t handle,
            void *buf,
            uint32_t size,
            uint32_t count);

int32_t
WHBCloseFile(int32_t handle);

char *
WHBReadWholeFile(const char *path,
                 uint32_t *outSize);

void
WHBFreeWholeFile(char *file);

#ifdef __cplusplus
}
#endif

/** @} */
