#include <coreinit/memdefaultheap.h>
#include <coreinit/filesystem.h>
#include <string.h>
#include <whb/file.h>
#include <whb/log.h>

static BOOL
sInitialised = FALSE;

static FSClient
sClient;

static BOOL
InitFileSystem()
{
   if (!sInitialised) {
      FSInit();

      if (FSAddClient(&sClient, -1) != FS_STATUS_OK) {
         return FALSE;
      }

      sInitialised = TRUE;
   }

   return TRUE;
}

int32_t
WHBOpenFile(const char *path,
            const char *mode)
{
   FSCmdBlock cmd;
   FSStatus result;
   FSFileHandle handle;
   char tmp[256];
   tmp[0] = 0;

   if (!InitFileSystem()) {
      return WHB_FILE_FATAL_ERROR;
   }

   if (path[0] != '/') {
      strcat(tmp, "/vol/content/");
      strcat(tmp, path);
   } else {
      strcat(tmp, path);
   }

   FSInitCmdBlock(&cmd);
   result = FSOpenFile(&sClient, &cmd, tmp, mode, &handle, -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSOpenFile error %d", __FUNCTION__, result);
      return WHB_FILE_FATAL_ERROR;
   }

   return (int32_t)handle;
}

uint32_t
WHBGetFileSize(int32_t handle)
{
   FSCmdBlock cmd;
   FSStatus result;
   FSStat stat;
   FSInitCmdBlock(&cmd);
   result = FSGetStatFile(&sClient, &cmd, (FSFileHandle)handle, &stat, -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSGetStatFile error %d", __FUNCTION__, result);
      return 0;
   }

   return stat.size;
}

uint32_t
WHBReadFile(int32_t handle,
            void *buf,
            uint32_t size,
            uint32_t count)
{
   FSCmdBlock cmd;
   FSStatus result;
   FSInitCmdBlock(&cmd);
   result = FSReadFile(&sClient, &cmd, buf, size, count, (FSFileHandle)handle, 0, -1);
   if (result < 0) {
      WHBLogPrintf("%s: FSReadFile error %d", __FUNCTION__, result);
      return 0;
   }

   return (uint32_t)result;
}

int32_t
WHBCloseFile(int32_t handle)
{
   FSCmdBlock cmd;
   FSStatus result;
   FSInitCmdBlock(&cmd);
   result = FSCloseFile(&sClient, &cmd, (FSFileHandle)handle, -1);
   if (result != FS_STATUS_OK) {
      WHBLogPrintf("%s: FSCloseFile error %d", __FUNCTION__, result);
      return WHB_FILE_FATAL_ERROR;
   }

   return WHB_FILE_OK;
}

char *
WHBReadWholeFile(const char *path,
                 uint32_t *outSize)
{
   int32_t handle;
   uint32_t size;
   char *buf = NULL;
   handle = WHBOpenFile(path, "r");
   if (handle == WHB_FILE_FATAL_ERROR) {
      WHBLogPrintf("%s: WHBOpenFile failed", __FUNCTION__);
      return NULL;
   }

   size = WHBGetFileSize(handle);
   if (size == 0) {
      goto error;
   }

   buf = MEMAllocFromDefaultHeapEx(size, 64);
   if (!buf) {
      WHBLogPrintf("%s: MEMAllocFromDefaultHeapEx(0x%X, 64) failed", __FUNCTION__, size);
      goto error;
   }

   if (WHBReadFile(handle, buf, 1, size) != size) {
      goto error;
   }

   if (outSize) {
      *outSize = size;
   }

   WHBCloseFile(handle);
   return buf;

error:
   if (buf) {
      MEMFreeToDefaultHeap(buf);
   }

   WHBCloseFile(handle);
   return NULL;
}

void
WHBFreeWholeFile(char *file)
{
   MEMFreeToDefaultHeap(file);
}
