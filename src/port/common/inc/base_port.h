#ifndef __BASE_PORT_H__
#define __BASE_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/event/inc/event_handler.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_PORT_VALUE_LOW                 0
#define BASE_PORT_VALUE_HIGH                1
#define BASE_PORT_PARAMETER_RESERVED        0

#define BASE_PORT_EVENT_PARAMETER_BASE      \
    {._reserved = EVENT_PARAMETER_RESERVED}

#define LinkedListNode2BasePort(instance)   \
    BASE2SUB(instance, BasePort, base)

#define EventParameter2BasePortEventParameter(instance) \
    BASE2SUB(instance, BasePortEventParameter, base)

struct BasePortVtbl;

typedef struct {
    const struct BasePortVtbl *vtbl;
} BasePort;

typedef struct {
    unsigned int _reserved;
} BasePortParameter;

typedef enum {
    BASE_PORT_MODE_INPUT,
    BASE_PORT_MODE_OUTPUT,
    BASE_PORT_MODE_INPUT_PULLUP
} BasePortMode;

typedef enum {
    BASE_PORT_EVENT_VALUE_CHANGED
} BasePortEvent;

typedef struct {
    EventParameter base;
    BasePortEvent event;
} BasePortEventParameter;

typedef struct BasePortVtbl {
    void (*Setup)(BasePort *self, unsigned int pin, BasePortMode mode);
    unsigned int (*Read)(BasePort *self, unsigned int pin);
    void (*Write)(BasePort *self, unsigned int pin, unsigned int value);
    void (*AddEventHandler)(BasePort *self, EventHandler *handler);
    void (*Sample)(BasePort *self);
} BasePortVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBasePort(
    BasePort *instance,
    BasePortParameter *parameter);

PROTECTED void DestructBasePort(BasePort *instance);

// Public method(s)
PUBLIC void SetupBasePort(BasePort *self, unsigned int pin, BasePortMode mode);
PUBLIC unsigned int ReadBasePort(BasePort *self, unsigned int pin);
PUBLIC void WriteBasePort(BasePort *self, unsigned int pin, unsigned int value);
PUBLIC void AddEventHandlerToBasePort(BasePort *self, EventHandler *handler);
PUBLIC void SampleBasePort(BasePort *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_PORT_H__
