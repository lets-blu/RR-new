#ifndef __GENERAL_UART_SERIAL_H__
#define __GENERAL_UART_SERIAL_H__

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_UART_SERIAL "GeneralUARTSerial"

#define GENERAL_UART_SERIAL_PARAMETER_BASE \
    {._reserved = BASE_SERIAL_PARAMETER_RESERVED}

#define BaseSerialParameter2GeneralUARTSerialParameter(instance) \
    BASE2SUB(instance, GeneralUARTSerialParameter, base)

typedef struct {
    BaseSerialParameter base;
    void *port;
    unsigned long baudrate;
} GeneralUARTSerialParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_UART_SERIAL_H__
