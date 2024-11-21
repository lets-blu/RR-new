#ifndef __BASE_PORT_H__
#define __BASE_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_PORT_VALUE_LOW                 0
#define BASE_PORT_VALUE_HIGH                1
#define BASE_PORT_PARAMETER_RESERVED        0

#define STATIC_BASE_PORT(baseVtbl) {        \
    .base = STATIC_LINKED_LIST_NODE(),      \
    .vtbl = (baseVtbl)                      \
}

#define LinkedListNode2BasePort(instance)   \
    BASE2SUB(instance, BasePort, base)

struct BasePortVtbl;

typedef struct {
    LinkedListNode base;
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

typedef struct BasePortVtbl {
    void (*Setup)(BasePort *self, unsigned int pin, BasePortMode mode);
    void (*Sample)(BasePort *self);
    unsigned int (*Read)(BasePort *self, unsigned int pin);
    void (*Write)(BasePort *self, unsigned int pin, unsigned int value);
} BasePortVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBasePort(
    BasePort *instance,
    BasePortParameter *parameter);

PROTECTED void DestructBasePort(BasePort *instance);

// Public method(s)
PUBLIC void SetupBasePort(BasePort *self, unsigned int pin, BasePortMode mode);
PUBLIC void SampleBasePort(BasePort *self);
PUBLIC unsigned int ReadBasePort(BasePort *self, unsigned int pin);
PUBLIC void WriteBasePort(BasePort *self, unsigned int pin, unsigned int value);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_PORT_H__
