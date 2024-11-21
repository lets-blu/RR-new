#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/arduino_digital_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define STATIC_ARDUINO_DIGITAL_PORT(port) { \
    .base   = STATIC_BASE_PORT(&baseVtbl),  \
    ._port  = (port),                       \
    ._mode  = 0,                            \
    ._value = 0                             \
}

// Private method(s)
PRIVATE void ConstructArduinoDigitalPort(
    ArduinoDigitalPort *instance,
    ArduinoDigitalPortParameter *parameter);

// Override method(s)
PUBLIC void SetupArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode);

PUBLIC void SampleArduinoDigitalPortBase(
    BasePort *port);

PUBLIC unsigned int ReadArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin);

PUBLIC void WriteArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    unsigned int value);

// Virtual methods table
static const BasePortVtbl baseVtbl = {
    .Setup = SetupArduinoDigitalPortBase,
    .Sample = SampleArduinoDigitalPortBase,
    .Read = ReadArduinoDigitalPortBase,
    .Write = WriteArduinoDigitalPortBase
};

PRIVATE STATIC ArduinoDigitalPort ports[] = {
    STATIC_ARDUINO_DIGITAL_PORT(NULL)
};

// Method implement(s)
PRIVATE void ConstructArduinoDigitalPort(
    ArduinoDigitalPort *instance,
    ArduinoDigitalPortParameter *parameter)
{
    if (instance == NULL || parameter == NULL)
    {
        return;
    }

    ConstructBasePort(&instance->base, &parameter->base);
    instance->base.vtbl = NULL;

    instance->_port = parameter->port;
    instance->_mode = 0;
    instance->_value = 0;
}

PUBLIC void DestructArduinoDigitalPort(ArduinoDigitalPort *instance)
{
    if (instance != NULL)
    {
        DestructBasePort(&instance->base);
        memset(instance, 0, sizeof(ArduinoDigitalPort));
    }
}

PUBLIC void SetupArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode)
{
    (void)port;

    switch (mode)
    {
        case BASE_PORT_MODE_INPUT:
        {
            pinMode(pin, INPUT);
            break;
        }

        case BASE_PORT_MODE_OUTPUT:
        {
            pinMode(pin, OUTPUT);
            break;
        }

        case BASE_PORT_MODE_INPUT_PULLUP:
        {
            pinMode(pin, INPUT_PULLUP);
            break;
        }

        default:
        {
            break;
        }
    }
}

PUBLIC void SampleArduinoDigitalPortBase(
    BasePort *port)
{
    (void)port;
}

PUBLIC unsigned int ReadArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin)
{
    (void)port;
    return digitalRead(pin);
}

PUBLIC void WriteArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    unsigned int value)
{
    (void)port;
    digitalWrite(pin, value);
}

PUBLIC STATIC bool FindCallbackOfArduinoDigitalPort(
    LinkedListNode *node,
    const void *data)
{
    ArduinoDigitalPort *self = LinkedListNode2ArduinoDigitalPort(node);
    return (node == NULL) ? false : (self->_port == data);
}

PUBLIC STATIC ArduinoDigitalPort *InstanceOfArduinoDigitalPort(uint8_t *port)
{
    for (unsigned int i = 0; i < ARDUINO_DIGITAL_PORTS_NUMBER; i++)
    {
        if (ports[i]._port == port)
        {
            return &ports[i];
        }
    }

    return NULL;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
