#ifndef __GENERAL_PORT_H__
#define __GENERAL_PORT_H__

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_ANALOG_PORT     "GeneralAPort"
#define GENERAL_DIGITAL_PORT    "GeneralDPort"

#define GENERAL_PORT_PARAMETER_BASE \
    {BASE_PORT_PARAMETER_RESERVED}

#define BasePortParameter2GeneralPortParameter(instance) \
    BASE2SUB(instance, GeneralPortParameter, base)

typedef struct {
    BasePortParameter base;
    void *port;
    unsigned int pin;
} GeneralPortParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_PORT_H__
