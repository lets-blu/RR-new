#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/arduino_uart_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC unsigned int ReadArduinoUARTSerialBase(
    BaseSerial *serial,
    uint8_t *buffer,
    unsigned int size);

PUBLIC unsigned int WriteArduinoUARTSerialBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    unsigned int size);

PUBLIC void AddEventHandlerToArduinoUARTSerialBase(
    BaseSerial *serial,
    EventHandler *handler);

PUBLIC void SampleArduinoUARTSerialBase(BaseSerial *serial);

// Virtual methods table
static const BaseSerialVtbl baseVtbl = {
    .Read = ReadArduinoUARTSerialBase,
    .Write = WriteArduinoUARTSerialBase,
    .AddEventHandler = AddEventHandlerToArduinoUARTSerialBase,
    .Sample = SampleArduinoUARTSerialBase
};

// Method implement(s)
PUBLIC void ConstructArduinoUARTSerial(
    ArduinoUARTSerial *instance,
    ArduinoUARTSerialParameter *parameter)
{
    if (instance == NULL || parameter == NULL)
    {
        return;
    }

    ConstructBaseSerial(&instance->base, &parameter->base);
    instance->base.vtbl = &baseVtbl;

    instance->_buffer = parameter->buffer;
    ConstructLinkedList(&instance->_handlers);
    Serial.begin(parameter->baudrate);
}

PUBLIC void DestructArduinoUARTSerial(ArduinoUARTSerial *instance)
{
    if (instance != NULL)
    {
        DestructLinkedList(&instance->_handlers);
        DestructBaseSerial(&instance->base);
        memset(instance, 0, sizeof(ArduinoUARTSerial));
    }
}

PUBLIC unsigned int ReadArduinoUARTSerialBase(
    BaseSerial *serial,
    uint8_t *buffer,
    unsigned int size)
{
    ArduinoUARTSerial *self = BaseSerial2ArduinoUARTSerial(serial);

    if (serial != NULL && self->_buffer != NULL)
    {
        return ReadRingBuffer(self->_buffer, buffer, size);
    }

    return Serial.readBytes(buffer, size);
}

PUBLIC unsigned int WriteArduinoUARTSerialBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    unsigned int size)
{
    (void)serial;
    return Serial.write(buffer, size);
}

PUBLIC void AddEventHandlerToArduinoUARTSerialBase(
    BaseSerial *serial,
    EventHandler *handler)
{
    ArduinoUARTSerial *self = BaseSerial2ArduinoUARTSerial(serial);

    if (serial != NULL && handler != NULL)
    {
        AddNodeToLinkedList(&self->_handlers, &handler->base);
    }
}

PUBLIC void SampleArduinoUARTSerialBase(BaseSerial *serial)
{
    ArduinoUARTSerial *self = BaseSerial2ArduinoUARTSerial(serial);

    if (serial == NULL || self->_buffer == NULL)
    {
        return;
    }

    if (Serial.available() > 0)
    {
        BaseSerialEventParameter parameter = {
            .base = BASE_SERIAL_EVENT_PARAMETER_BASE,
            .event = BASE_SERIAL_EVENT_DATA_RECEIVED,
            .buffer = self->_buffer
        };

        uint8_t data = Serial.read();
        WriteRingBuffer(self->_buffer, &data, 1);
        InvokeEventHandlers(&self->_handlers, self, &parameter.base);
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
