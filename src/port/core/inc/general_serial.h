#ifndef __GENERAL_SERIAL_H__
#define __GENERAL_SERIAL_H__

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_UART_SERIAL "GeneralUARTSerial"
#define GENERAL_SPI_SERIAL "GeneralSPISerial"
#define GENERAL_I2C_SERIAL "GeneralI2CSerial"

#define GENERAL_SERIAL_PARAMETER_BASE {          \
    ._reserved = BASE_SERIAL_PARAMETER_RESERVED, \
}

#define BaseSerialParameter2GeneralSerialParameter(pThis) \
    CONTAINER_OF(pThis, GeneralSerialParameter, base)

typedef struct {
    BaseSerialParameter base;
    void *serial;
    unsigned long baudrate;
} GeneralSerialParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_SERIAL_H__
