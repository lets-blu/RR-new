#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/ArduinoDPort.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC void SetupArduinoDPortBase(BasePort *port, BasePortMode mode);
PUBLIC unsigned int ReadArduinoDPortBase(BasePort *port);
PUBLIC void WriteArduinoDPortBase(BasePort *port, unsigned int value);

// Virtual methods table
static const BasePortVtbl baseVtbl = {
    .Setup = SetupArduinoDPortBase,
    .Read = ReadArduinoDPortBase,
    .Write = WriteArduinoDPortBase
};

// Method implement(s)
PUBLIC void ConstructArduinoDPort(
    ArduinoDPort *instance,
    ArduinoDPortParameter *parameter)
{
    if (instance != NULL && parameter != NULL)
    {
        ConstructBasePort(&instance->base, &parameter->base);
        instance->_pin = parameter->pin;
        instance->base.vtbl = &baseVtbl;
    }
}

PUBLIC void DestructArduinoDPort(ArduinoDPort *instance)
{
    if (instance != NULL)
    {
        DestructBasePort(&instance->base);
        memset(instance, 0, sizeof(ArduinoDPort));
    }
}

PUBLIC void SetupArduinoDPortBase(BasePort *port, BasePortMode mode)
{
    ArduinoDPort *self = BasePort2ArduinoDPort(port);

    if (port == NULL)
    {
        return;
    }

    switch (mode)
    {
        case BASE_PORT_MODE_INPUT:
        {
            pinMode(self->_pin, INPUT);
            break;
        }

        case BASE_PORT_MODE_OUTPUT:
        {
            pinMode(self->_pin, OUTPUT);
            break;
        }

        case BASE_PORT_MODE_INPUT_PULLUP:
        {
            pinMode(self->_pin, INPUT_PULLUP);
            break;
        }

        default:
        {
            break;
        }
    }
}

PUBLIC unsigned int ReadArduinoDPortBase(BasePort *port)
{
    ArduinoDPort *self = BasePort2ArduinoDPort(port);
    return (port == NULL) ? 0 : digitalRead(self->_pin);
}

PUBLIC void WriteArduinoDPortBase(BasePort *port, unsigned int value)
{
    ArduinoDPort *self= BasePort2ArduinoDPort(port);

    if (port != NULL)
    {
        digitalWrite(self->_pin, value);
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
