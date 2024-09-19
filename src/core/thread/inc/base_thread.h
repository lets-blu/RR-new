#ifndef __BASE_THREAD_H__
#define __BASE_THREAD_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#define BEGIN_BASE_THREAD(self)                     \
    switch ((self)->_line)                          \
    {                                               \
        case 0:

#define END_BASE_THREAD(self)                       \
    }                                               \
    return BASE_THREAD_STATE_ENDED

#define DELAY_BASE_THREAD(self, delay)              \
    do                                              \
    {                                               \
        UpdateTickInBaseThread(self);               \
        (self)->_line = __LINE__; case __LINE__:    \
        if (!IsTimeoutOfBaseThread(self, delay))    \
        {                                           \
            return BASE_THREAD_STATE_WAITING;       \
        }                                           \
    } while (0);

#define LinkedListNode2BaseThread(instance)         \
    BASE2SUB(instance, BaseThread, base)

struct BaseThreadVtbl;

typedef enum {
    BASE_THREAD_STATE_ENDED,
    BASE_THREAD_STATE_WAITING
} BaseThreadState;

typedef struct {
    LinkedListNode base;
    unsigned int _line;
    unsigned long _tick;
    const struct BaseThreadVtbl* vtbl;
} BaseThread;

typedef struct BaseThreadVtbl {
    BaseThreadState (*Run)(BaseThread *);
} BaseThreadVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseThread(BaseThread *instance);
PROTECTED void DestructBaseThread(BaseThread *instance);

// Public method(s)
PUBLIC void UpdateTickInBaseThread(BaseThread *self);
PUBLIC bool IsTimeoutOfBaseThread(BaseThread *self, unsigned long delay);
PUBLIC BaseThreadState RunBaseThread(BaseThread *self);

PUBLIC STATIC void RunBaseThreads(LinkedList *threads);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_THREAD_H__
