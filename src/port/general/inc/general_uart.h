#ifndef __GENERAL_UART_H__
#define __GENERAL_UART_H__

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_UART_SERIAL "GeneralUART"

#define GENERAL_UART_PARAMETER_BASE \
    {BASE_SERIAL_PARAMETER_RESERVED}

#define BaseSerialParameter2GeneralUARTParameter(instance) \
    BASE2SUB(instance, GeneralUARTParameter, base)

typedef struct {
    BaseSerialParameter base;
    void *port;
    unsigned long baudrate;
} GeneralUARTParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_UART_H__
