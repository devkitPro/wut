#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <curl/curl.h>

#include <nsysnet/socket.h>
#include <nsysnet/nssl.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MemoryStruct
{
   char *memory;
   size_t size;
};

static size_t
writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
   size_t realsize = size * nmemb;
   struct MemoryStruct *mem = (struct MemoryStruct *)userp;

   mem->memory = realloc(mem->memory, mem->size + realsize + 1);
   if(mem->memory == NULL) {
      WHBLogPrintf("WriteMemoryCallback: Not enough memory (realloc returned NULL)\n");
      return 0;
   }

   memcpy(&(mem->memory[mem->size]), contents, realsize);
   mem->size += realsize;
   mem->memory[mem->size] = 0;
   return realsize;
}

static int
progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
   WHBLogPrintf("ProcessCallback %f / %f", dlnow, dltotal);
   WHBLogConsoleDraw();
   return 0;
}

static int
debugCallback(CURL *handle,
              curl_infotype type,
              char *data,
              size_t size,
              void *userp)
{
   switch(type) {
   case CURLINFO_TEXT:
      WHBLogPrintf("== Info: %s", data);
      break;
   case CURLINFO_HEADER_OUT:
      WHBLogPrintf("=> Send header");
      break;
   case CURLINFO_DATA_OUT:
      WHBLogPrintf("=> Send data");
      break;
   case CURLINFO_SSL_DATA_OUT:
      WHBLogPrintf("=> Send SSL data");
      break;
   case CURLINFO_HEADER_IN:
      WHBLogPrintf("<= Recv header");
      break;
   case CURLINFO_DATA_IN:
      WHBLogPrintf("<= Recv data");
      break;
   case CURLINFO_SSL_DATA_IN:
      WHBLogPrintf("<= Recv SSL data");
      break;
   }
   return 0;
}

int
main(int argc, char **argv)
{
   NSSLContextHandle context = -1;
   CURL *curl = NULL;
   int ret = 0;
   int resp = 404;
   struct MemoryStruct chunk;
   chunk.memory = malloc(1);
   chunk.size = 0;

   WHBProcInit();
   WHBLogConsoleInit();
   WHBLogPrintf("Initialising libraries...");

   socket_lib_init();
   ret = NSSLInit();
   if (ret < 0) {
      WHBLogPrintf("NSSLInit failed with error %d.", ret);
      goto exit;
   }

   curl = curl_easy_init();
   if (!curl) {
      WHBLogPrintf("curl_easy_init failed.");
      goto exit;
   }

   context = NSSLCreateContext(0);
   if (context < 0) {
      WHBLogPrintf("NSSLCreateContext failed with error %d.", context);
      goto exit;
   }

   for(int i = NSSL_SERVER_CERT_GROUP_NINTENDO_FIRST; i <= NSSL_SERVER_CERT_GROUP_NINTENDO_LAST; ++i) {
      ret = NSSLAddServerPKI(context, i);
      if (ret < 0) {
         WHBLogPrintf("NSSLAddServerPKI(context, %d) failed with error %d.", i, ret);
      }
   }

   for(int i = NSSL_SERVER_CERT_GROUP_COMMERCIAL_FIRST; i <= NSSL_SERVER_CERT_GROUP_COMMERCIAL_LAST; ++i) {
      NSSLAddServerPKI(context, i);
      if (ret < 0) {
         WHBLogPrintf("NSSLAddServerPKI(context, %d) failed with error %d.", i, ret);
      }
   }

   for(int i = NSSL_SERVER_CERT_GROUP_COMMERCIAL_4096_FIRST; i <= NSSL_SERVER_CERT_GROUP_COMMERCIAL_4096_LAST; ++i) {
      NSSLAddServerPKI(context, i);
      if (ret < 0) {
         WHBLogPrintf("NSSLAddServerPKI(context, %d) failed with error %d.", i, ret);
      }
   }

   ret = curl_easy_setopt(curl, CURLOPT_NSSL_CONTEXT, context);
   if (ret < 0) {
      WHBLogPrintf("curl_easy_setopt(CURLOPT_NSSL_CONTEXT) failed with error %d.", ret);
   }

   curl_easy_setopt(curl, CURLOPT_URL, "https://twitter.com/realDonaldTrump");
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

   curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
   curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, NULL);
   curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

   curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debugCallback);
   curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);

   WHBLogConsoleDraw();
   ret = curl_easy_perform(curl);
   if (ret) {
      WHBLogPrintf("curl_easy_perform returned %d", ret);
      goto exit;
   }

   curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp);
   WHBLogPrintf("Response code: %d", resp);
   WHBLogPrintf("chunk.size = %u", chunk.size);

   // Try parse the tweet
   if (chunk.size) {
      // <div class="js-tweet-text-container
      char *start, *end;
      start = strstr(chunk.memory, "js-tweet-text-container");
      if (start) {
         // >
         start = strchr(start, '>') + 1;
      }
      if (start) {
         // <p ... >
         start = strchr(start, '>') + 1;
      }
      if (start) {
         end = strstr(start, "</p>");
      }

      if (!start || !end) {
         WHBLogPrintf("Could not find tweet text");
      } else {
         char *pos = start;
         *end = 0;
         WHBLogPrintf("I am sorry you have to read this:");

         // Break into lines
         while (pos < end) {
            char sep = *(pos + 50);
            *(pos + 50) = 0;
            WHBLogPrintf(pos);
            *(pos + 50) = sep;
            pos += 50;
         }
      }
   }

exit:
   while(WHBProcIsRunning()) {
      WHBLogConsoleDraw();
      OSSleepTicks(OSMillisecondsToTicks(100));
   }

   WHBLogPrintf("Cleaning up libraries...");
   free(chunk.memory);
   curl_easy_cleanup(curl);
   NSSLFinish();
   socket_lib_finish();

   WHBLogPrintf("Exiting... good bye.");
   WHBLogConsoleDraw();
   OSSleepTicks(OSMillisecondsToTicks(1000));

   WHBLogConsoleFree();
   WHBProcShutdown();
   return 0;
}
