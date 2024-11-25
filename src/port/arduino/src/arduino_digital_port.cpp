#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/arduino_digital_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC void SetupArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode);

PUBLIC unsigned int ReadArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin);

PUBLIC void WriteArduinoDigitalPortBase(
    BasePort *port,
    unsigned int pin,
    unsigned int value);

PUBLIC void AddEventHandlerToArduinoDigitalPortBase(
    BasePort *port,
    EventHandler *handler);

PUBLIC void SampleArduinoDigitalPortBase(BasePort *port);

// Virtual methods table
static const BasePortVtbl baseVtbl = {
    .Setup = SetupArduinoDigitalPortBase,
    .Read = ReadArduinoDigitalPortBase,
    .Write = WriteArduinoDigitalPortBase,
    .AddEventHandler = AddEventHandlerToArduinoDigitalPortBase,
    .Sample = SampleArduinoDigitalPortBase,
};

// Method implement(s)
PUBLIC void ConstructArduinoDigitalPort(
    ArduinoDigitalPort *instance,
    ArduinoDigitalPortParameter *parameter)
{
    if (instance != NULL && parameter != NULL)
    {
        ConstructBasePort(&instance->base, &parameter->base);
        instance->base.vtbl = &baseVtbl;
    }
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

PUBLIC void AddEventHandlerToArduinoDigitalPortBase(
    BasePort *port,
    EventHandler *handler)
{
    (void)port;
    (void)handler;
}

PUBLIC void SampleArduinoDigitalPortBase(BasePort *port)
{
    (void)port;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
