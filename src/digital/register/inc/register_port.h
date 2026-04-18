#ifndef __REGISTER_PORT_H__
#define __REGISTER_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define REGISTER_PORT_PARAMETER_BASE {         \
    ._reserved = BASE_PORT_PARAMETER_RESERVED, \
}

#define REGISTER_PORT_IS_CONSTRUCTED(pThis) \
    ((pThis)->base.vtbl != NULL)

#define BasePort2RegisterPort(pThis) \
    CONTAINER_OF(pThis, RegisterPort, base)

#define BasePortParameter2RegisterPortParameter(pThis) \
    CONTAINER_OF(pThis, RegisterPortParameter, base)

struct RegisterGroup;

typedef struct {
    BasePort base;
    struct RegisterGroup *_group;
} RegisterPort;

typedef struct {
    BasePortParameter base;
    struct RegisterGroup *group;
} RegisterPortParameter;

// Constructor(s) & Destructor(s)
PUBLIC void RegisterPort_Construct(
    RegisterPort *pThis,
    RegisterPortParameter *parameter);

PUBLIC void RegisterPort_Destruct(RegisterPort *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __REGISTER_PORT_H__
