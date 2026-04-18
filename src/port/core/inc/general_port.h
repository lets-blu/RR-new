#ifndef __GENERAL_PORT_H__
#define __GENERAL_PORT_H__

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_ANALOG_PORT "GeneralAnalogPort"
#define GENERAL_DIGITAL_PORT "GeneralDigitalPort"
#define GENERAL_ADDRESS_PORT "GeneralAddressPort"

#define GENERAL_PORT_PARAMETER_BASE {          \
    ._reserved = BASE_PORT_PARAMETER_RESERVED, \
}

#define BasePortParameter2GeneralPortParameter(pThis) \
    CONTAINER_OF(pThis, GeneralPortParameter, base)

typedef struct {
    BasePortParameter base;
    void *port;
} GeneralPortParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_PORT_H__
