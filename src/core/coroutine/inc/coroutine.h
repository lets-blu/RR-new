#ifndef __COROUTINE_H__
#define __COROUTINE_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_core.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define COROUTINE_STATIC() { \
    ._line = 0,              \
}

#define COROUTINE_INIT(pThis) \
    (pThis)->_line = 0

#define COROUTINE_BEGIN(pThis) \
    bool __yield = false;      \
    (void)__yield;             \
    switch ((pThis)->_line) {  \
        case 0:

#define COROUTINE_END(pThis) \
    }                        \
    __yield = true;          \
    (pThis)->_line = 0;      \
    return COROUTINE_STATE_ENDED

#define COROUTINE_YIELD(pThis)                  \
    do {                                        \
        __yield = true;                         \
        (pThis)->_line = __LINE__;              \
        case __LINE__:                          \
            if (__yield) {                      \
                return COROUTINE_STATE_YIELDED; \
            }                                   \
    } while (0)

#define COROUTINE_SLEEP(pThis, delay)                 \
    do {                                              \
        static unsigned long pre;                     \
        pre = Coroutine_GetTime();                    \
        (pThis)->_line = __LINE__;                    \
        case __LINE__:                                \
            if (!Coroutine_IsTimeout(pre, (delay))) { \
                return COROUTINE_STATE_WAITING;       \
            }                                         \
    } while (0)

typedef enum {
    COROUTINE_STATE_ENDED,
    COROUTINE_STATE_YIELDED,
    COROUTINE_STATE_WAITING,
} CoroutineState;

typedef struct {
    unsigned int _line;
} Coroutine;

// Constructor(s) & Destructor(s)
PUBLIC void Coroutine_Construct(Coroutine *pThis);
PUBLIC void Coroutine_Destruct(Coroutine *pThis);

// Public method(s)
PUBLIC STATIC unsigned long Coroutine_GetTime(void);
PUBLIC STATIC bool Coroutine_IsTimeout(unsigned long pre, unsigned long delay);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __COROUTINE_H__
