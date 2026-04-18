#ifndef __LINKED_COROUTINE_H__
#define __LINKED_COROUTINE_H__

#include <stddef.h>
#include <string.h>

#include "core/coroutine/inc/coroutine.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LINKED_COROUTINE_INIT(pThis) \
    COROUTINE_INIT(&(pThis)->_coroutine)

#define LINKED_COROUTINE_BEGIN(pThis) \
    COROUTINE_BEGIN(&(pThis)->_coroutine)

#define LINKED_COROUTINE_END(pThis) \
    COROUTINE_END(&(pThis)->_coroutine)

#define LINKED_COROUTINE_YIELD(pThis) \
    COROUTINE_YIELD(&(pThis)->_coroutine)

#define LINKED_COROUTINE_SLEEP(pThis, delay) \
    COROUTINE_SLEEP(&(pThis)->_coroutine, (delay))

#define LinkedListNode2LinkedCoroutine(pThis) \
    CONTAINER_OF(pThis, LinkedCoroutine, base)

struct LinkedCoroutineVtbl;

typedef struct {
    LinkedListNode base;
    Coroutine _coroutine;
    const struct LinkedCoroutineVtbl *vtbl;
} LinkedCoroutine;

typedef struct LinkedCoroutineVtbl {
    CoroutineState (*Run)(LinkedCoroutine *);
} LinkedCoroutineVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void LinkedCoroutine_Construct(LinkedCoroutine *pThis);
PROTECTED void LinkedCoroutine_Destruct(LinkedCoroutine *pThis);

// Public method(s)
PUBLIC CoroutineState LinkedCoroutine_Run(LinkedCoroutine *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LINKED_COROUTINE_H__
