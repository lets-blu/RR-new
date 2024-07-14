#ifndef __BASE_PORT_H__
#define __BASE_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include "core/common/inc/Keywords.h"

#define BASE_PORT_VALUE_LOW             0
#define BASE_PORT_VALUE_HIGH            1

#define BASE_PORT_PARAMETER_RESERVED    0

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

typedef struct BasePortVtbl {
    void (*Setup)(BasePort *, BasePortMode);
    unsigned int (*Read)(BasePort *);
    void (*Write)(BasePort *, unsigned int);
} BasePortVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBasePort(
    BasePort *instance,
    BasePortParameter *parameter);

PROTECTED void DestructBasePort(BasePort *instance);

// Public method(s)
PUBLIC void SetupBasePort(BasePort *self, BasePortMode mode);
PUBLIC unsigned int ReadBasePort(BasePort *self);
PUBLIC void WriteBasePort(BasePort *self, unsigned int value);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_PORT_H__