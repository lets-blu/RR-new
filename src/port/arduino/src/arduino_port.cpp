#include "port/arduino/inc/arduino_port.h"

// Private member(s)
#if defined(ARDUINO_ARCH_AVR)
PRIVATE STATIC volatile uint8_t *const avrPorts[] = {&PORTB, &PORTC, &PORTD};
#endif // ARDUINO_ARCH_AVR

// Virtual method(s)
PUBLIC void ArduinoPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode);

PUBLIC unsigned int ArduinoPort_Read(
    BasePort *port,
    unsigned int pin);

PUBLIC void ArduinoPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value);

// Virtual methods table(s)
static const BasePortVtbl baseVtbl = {
    .SetMode = ArduinoPort_SetMode,
    .Read = ArduinoPort_Read,
    .Write = ArduinoPort_Write,
};

// Method implement(s)
PUBLIC void ArduinoPort_Construct(
    ArduinoPort *pThis,
    ArduinoPortParameter *parameter)
{
    if (pThis != NULL && parameter != NULL) {
        BasePort_Construct(&pThis->base, &parameter->base);
        pThis->base.vtbl = &baseVtbl;
        pThis->_port = parameter->port;
    }
}

PUBLIC void ArduinoPort_Destruct(ArduinoPort *pThis)
{
    if (pThis != NULL) {
        BasePort_Destruct(&pThis->base);
    }
}

PUBLIC void *ArduinoPort_GetPort(ArduinoPort *pThis)
{
    return (pThis == NULL) ? NULL : pThis->_port;
}

PUBLIC STATIC bool ArduinoPort_IsValidPort(void *port)
{
    if (port == NULL) {
        return true;
    }

#if defined(ARDUINO_ARCH_AVR)
    for (unsigned int i = 0; i < ARDUINO_PORT_AVR_PORTS_NUMBER; i++) {
        if (port == avrPorts[i]) {
            return true;
        }
    }
#endif // ARDUINO_ARCH_AVR

    return false;
}

PUBLIC void ArduinoPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode)
{
    ArduinoPort *pThis = BasePort2ArduinoPort(port);

    if (port == NULL) {
        return;
    }

    switch (mode) {
        case BASE_PORT_MODE_INPUT: {
            if (pThis->_port != NULL) {
#if defined(ARDUINO_ARCH_AVR)
                *ARDUINO_PORT_GET_AVR_DDR(pThis->_port) &= ~pin;
#endif // ARDUINO_ARCH_AVR
                break;
            }

            pinMode(pin, INPUT);
            break;
        }

        case BASE_PORT_MODE_OUTPUT: {
            if (pThis->_port != NULL) {
#if defined(ARDUINO_ARCH_AVR)
                *ARDUINO_PORT_GET_AVR_DDR(pThis->_port) |= pin;
#endif // ARDUINO_ARCH_AVR
                break;
            }

            pinMode(pin, OUTPUT);
            break;
        }

        case BASE_PORT_MODE_INPUT_PULLUP: {
            if (pThis->_port != NULL) {
#if defined(ARDUINO_ARCH_AVR)
                *ARDUINO_PORT_GET_AVR_DDR(pThis->_port) &= ~pin;
                *ARDUINO_PORT_GET_AVR_PORT(pThis->_port) |= pin;
#endif // ARDUINO_ARCH_AVR
                break;
            }

            pinMode(pin, INPUT_PULLUP);
            break;
        }

        default: {
            break;
        }
    }
}

PUBLIC unsigned int ArduinoPort_Read(
    BasePort *port,
    unsigned int pin)
{
    unsigned int value = 0;
    ArduinoPort *pThis = BasePort2ArduinoPort(port);

    if (port == NULL) {
        return 0;
    }

    if (pThis->_port != NULL) {
#if defined(ARDUINO_ARCH_AVR)
        value = *ARDUINO_PORT_GET_AVR_PIN(pThis->_port);
        return ((value & pin) >> BasePort_GetPinOffset(pin));
#else
        return 0;
#endif // ARDUINO_ARCH_AVR
    }

    if (digitalRead(pin) == LOW) {
        value = BASE_PORT_VALUE_LOW;
    } else {
        value = BASE_PORT_VALUE_HIGH;
    }

    return value;
}

PUBLIC void ArduinoPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value)
{
    ArduinoPort *pThis = BasePort2ArduinoPort(port);

    if (port == NULL) {
        return;
    }

    if (pThis->_port != NULL) {
#if defined(ARDUINO_ARCH_AVR)
        value = (value << BasePort_GetPinOffset(pin)) & pin;
        *ARDUINO_PORT_GET_AVR_PORT(pThis->_port) &= ~pin;
        *ARDUINO_PORT_GET_AVR_PORT(pThis->_port) |= value;
#endif // ARDUINO_ARCH_AVR
        return;
    }

    if (value == BASE_PORT_VALUE_LOW) {
        digitalWrite(pin, LOW);
    } else {
        digitalWrite(pin, HIGH);
    }
}
