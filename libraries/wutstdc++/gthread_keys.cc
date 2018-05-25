#include "include/bits/gthr-default.h"

struct gthread_key
{
   bool in_use;
   void (*dtor) (void *);
};

static gthread_key key_table[__GTHREAD_MAX_KEYS];

static __gthread_mutex_t key_mutex;
static __gthread_once_t init_once_control = __GTHREAD_ONCE_INIT;

static void init()
{
   __GTHREAD_MUTEX_INIT_FUNCTION(&key_mutex);
   memset(key_table, 0, sizeof(key_table));
}

int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
   int res = EAGAIN;
   __gthread_once(&init_once_control, init);
   __gthread_mutex_lock(&key_mutex);

   for (int i = 0; i < __GTHREAD_MAX_KEYS; ++i) {
      if (key_table[i].in_use) {
         continue;
      }

      key_table[i].in_use = 1;
      key_table[i].dtor = __dtor;

      res = 0;
      *__key = (__gthread_key_t)i;
      break;
   }

   __gthread_mutex_unlock(&key_mutex);
   return res;
}

int
__gthread_key_delete (__gthread_key_t __key)
{
   __gthread_mutex_lock(&key_mutex);
   key_table[__key].in_use = 0;
   key_table[__key].dtor = NULL;
   __gthread_mutex_unlock(&key_mutex);
   return -1;
}

static const void **
__gthread_get_thread_keys()
{
   const void **keys = (const void **)OSGetThreadSpecific(__GTHREAD_THREAD_SPECIFIC_ID);
   if (!keys) {
      MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
      keys = (const void **)MEMAllocFromExpHeapEx(heap, sizeof(void *) * sizeof(__GTHREAD_MAX_KEYS), 4);
      memset(keys, 0, sizeof(void *) * sizeof(__GTHREAD_MAX_KEYS));
      OSSetThreadSpecific(__GTHREAD_THREAD_SPECIFIC_ID, keys);
   }

   return keys;
}

void *
__gthread_getspecific (__gthread_key_t __key)
{
   return (void *)__gthread_get_thread_keys()[__key];
}

int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
   __gthread_get_thread_keys()[__key] = __ptr;
   return 0;
}

void
__gthread_key_cleanup (OSThread *thread)
{
   void **keys = (void **)OSGetThreadSpecific(__GTHREAD_THREAD_SPECIFIC_ID);
   if (!keys) {
      return;
   }

   __gthread_mutex_lock(&key_mutex);

   for (int i = 0; i < __GTHREAD_MAX_KEYS; ++i) {
      if (key_table[i].in_use && key_table[i].dtor && keys[i]) {
         key_table[i].dtor(keys[i]);
      }
   }

   __gthread_mutex_unlock(&key_mutex);
}
