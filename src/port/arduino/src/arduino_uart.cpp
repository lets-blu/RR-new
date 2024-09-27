#ifdef ARDUINO

#include "port/arduino/inc/arduino_uart.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC size_t ReadArduinoUARTBase(
    BaseSerial *serial,
    uint8_t *buffer,
    size_t size);

PUBLIC size_t WriteArduinoUARTBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    size_t size);

// Virtual methods table
static const BaseSerialVtbl baseVtbl = {
    .Read = ReadArduinoUARTBase,
    .Write = WriteArduinoUARTBase
};

// Method implement(s)
PUBLIC void ConstructArduinoUART(
    ArduinoUART *instance,
    ArduinoUARTParameter *parameter)
{
    if (instance == NULL || parameter == NULL || parameter->port == NULL)
    {
        return;
    }

    ConstructBaseSerial(&instance->base, &parameter->base);
    instance->base.vtbl = &baseVtbl;

    instance->_port = parameter->port;
    instance->_port->begin(parameter->baudrate);
}

PUBLIC void DestructArduinoUART(ArduinoUART *instance)
{
    if (instance != NULL)
    {
        DestructBaseSerial(&instance->base);
        memset(instance, 0, sizeof(ArduinoUART));
    }
}

PUBLIC size_t ReadArduinoUARTBase(
    BaseSerial *serial,
    uint8_t *buffer,
    size_t size)
{
    ArduinoUART *self = BaseSerial2ArduinoUART(serial);

    if (serial == NULL || self->_port == NULL)
    {
        return 0;
    }

    return self->_port->readBytes(buffer, size);
}

PUBLIC size_t WriteArduinoUARTBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    size_t size)
{
    ArduinoUART *self = BaseSerial2ArduinoUART(serial);

    if (serial == NULL || self->_port == NULL)
    {
        return 0;
    }

    return self->_port->write(buffer, size);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
