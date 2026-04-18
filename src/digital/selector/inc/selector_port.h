#ifndef __SELECTOR_PORT_H__
#define __SELECTOR_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SELECTOR_PORT_PARAMETER_BASE {         \
    ._reserved = BASE_PORT_PARAMETER_RESERVED, \
}

#define SELECTOR_PORT_IS_CONSTRUCTED(pThis) \
    ((pThis)->base.vtbl != NULL)

#define BasePort2SelectorPort(pThis) \
    CONTAINER_OF(pThis, SelectorPort, base)

#define BasePortParameter2SelectorPortParameter(pThis) \
    CONTAINER_OF(pThis, SelectorPortParameter, base)

struct SelectorGroup;

typedef struct {
    BasePort base;
    struct SelectorGroup *_group;
} SelectorPort;

typedef struct {
    BasePortParameter base;
    struct SelectorGroup *group;
} SelectorPortParameter;

// Constuctor(s) & Destructor(s)
PUBLIC void SelectorPort_Construct(
    SelectorPort *pThis,
    SelectorPortParameter *parameter);

PUBLIC void SelectorPort_Destruct(SelectorPort *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SELECTOR_PORT_H__
