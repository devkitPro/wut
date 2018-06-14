#include "wut_gthread.h"

#include <malloc.h>
#include <string.h>
#include <sys/errno.h>

struct __wut_key_table_entry
{
   bool in_use;
   void (*dtor) (void *);
};

static __wut_key_table_entry key_table[__WUT_MAX_KEYS];

static OSMutex key_mutex;
static __wut_once_t init_once_control = __WUT_ONCE_VALUE_INIT;

static void init()
{
   __wut_mutex_init_function(&key_mutex);
   memset(key_table, 0, sizeof(key_table));
}

int
__wut_key_create(__wut_key_t *key,
                 void (*dtor) (void *))
{
   int res = EAGAIN;
   __wut_once(&init_once_control, init);
   __wut_mutex_lock(&key_mutex);

   for (uint32_t i = 0; i < __WUT_MAX_KEYS; ++i) {
      if (key_table[i].in_use) {
         continue;
      }

      key_table[i].in_use = 1;
      key_table[i].dtor = dtor;

      res = 0;
      key->index = i;
      break;
   }

   __wut_mutex_unlock(&key_mutex);
   return res;
}

int
__wut_key_delete(__wut_key_t key)
{
   __wut_mutex_lock(&key_mutex);
   key_table[key.index].in_use = 0;
   key_table[key.index].dtor = NULL;
   __wut_mutex_unlock(&key_mutex);
   return -1;
}

static const void **
__wut_get_thread_keys()
{
   const void **keys = (const void **)OSGetThreadSpecific(__WUT_KEY_THREAD_SPECIFIC_ID);
   if (!keys) {
      keys = (const void **)malloc(sizeof(void *) * sizeof(__WUT_MAX_KEYS));
      if (!keys) {
         return NULL;
      }

      memset(keys, 0, sizeof(void *) * sizeof(__WUT_MAX_KEYS));
      OSSetThreadSpecific(__WUT_KEY_THREAD_SPECIFIC_ID, keys);
   }

   return keys;
}

void *
__wut_getspecific(__wut_key_t key)
{
   const void **keys = __wut_get_thread_keys();
   if (!keys) {
      return NULL;
   }

   return (void *)(keys[key.index]);
}

int
__wut_setspecific(__wut_key_t key,
                  const void *ptr)
{
   const void **keys = __wut_get_thread_keys();
   if (!keys) {
      return -1;
   }

   keys[key.index] = ptr;
   return 0;
}

void
__wut_key_cleanup(OSThread *thread)
{
   void **keys = (void **)OSGetThreadSpecific(__WUT_KEY_THREAD_SPECIFIC_ID);
   if (!keys) {
      return;
   }

   __wut_mutex_lock(&key_mutex);

   for (int i = 0; i < __WUT_MAX_KEYS; ++i) {
      if (key_table[i].in_use && key_table[i].dtor && keys[i]) {
         key_table[i].dtor(keys[i]);
      }
   }

   __wut_mutex_unlock(&key_mutex);
   free(keys);
}
