#ifndef __BASE_PORT_H__
#define __BASE_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_PORT_VALUE_LOW 0U
#define BASE_PORT_VALUE_HIGH 1U
#define BASE_PORT_PARAMETER_RESERVED 0U

struct BasePortVtbl;

typedef struct {
    const struct BasePortVtbl *vtbl;
} BasePort;

typedef enum {
    BASE_PORT_MODE_INPUT,
    BASE_PORT_MODE_OUTPUT,
    BASE_PORT_MODE_INPUT_PULLUP,
} BasePortMode;

typedef struct {
    unsigned int _reserved;
} BasePortParameter;

typedef struct BasePortVtbl {
    void (*SetMode)(BasePort *, unsigned int, BasePortMode);
    unsigned int (*Read)(BasePort *, unsigned int);
    void (*Write)(BasePort *, unsigned int, unsigned int);
} BasePortVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BasePort_Construct(
    BasePort *pThis,
    BasePortParameter *parameter);

PROTECTED void BasePort_Destruct(BasePort *pThis);

// Public method(s)
PUBLIC void BasePort_SetMode(
    BasePort *pThis,
    unsigned int pin,
    BasePortMode mode);

PUBLIC unsigned int BasePort_Read(BasePort *pThis, unsigned int pin);
PUBLIC void BasePort_Write(BasePort *pThis, unsigned int pin, unsigned int val);
PUBLIC STATIC unsigned int BasePort_GetPinOffset(unsigned int pin);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_PORT_H__
