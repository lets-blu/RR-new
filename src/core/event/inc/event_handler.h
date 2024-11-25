#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define EVENT_PARAMETER_RESERVED                0

#define STATIC_EVENT_HANDLER(handler) {         \
    .base = STATIC_LINKED_LIST_NODE(),          \
    ._handler = (handler)                       \
}

#define LinkedListNode2EventHandler(instance)   \
    BASE2SUB(instance, EventHandler, base)

typedef struct {
    unsigned int _reserved;
} EventParameter;

typedef struct {
    LinkedListNode base;

    void (*_handler)(
        void *sender,
        EventParameter *parameter);
} EventHandler;

typedef void (*EventHandlerHandler)(
    void *sender,
    EventParameter *parameter);

// Constructor(s) & Destructor(s)
PUBLIC void ConstructEventHandler(
    EventHandler *instance,
    EventHandlerHandler handler);

PUBLIC void DestructEventHandler(
    EventHandler *instance);

// Public Method(s)
PUBLIC void InvokeEventHandler(
    EventHandler *self,
    void *sender,
    EventParameter *parameter);

PUBLIC STATIC void InvokeEventHandlers(
    LinkedList *handlers,
    void *sender,
    EventParameter *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __EVENT_HANDLER_H__
