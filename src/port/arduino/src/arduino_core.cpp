#include "port/arduino/inc/arduino_core.h"

// Private method(s)
PRIVATE ArduinoPort *ArduinoCore_AllocPort(
    ArduinoCore *pThis,
    void *port);

PRIVATE ArduinoSerial *ArduinoCore_AllocSerial(
    ArduinoCore *pThis,
    HardwareSerial *serial);

// Override method(s)
PUBLIC BasePort *ArduinoCore_CreatePort(
    BaseCore *core,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void ArduinoCore_DestroyPort(BaseCore *core, BasePort *port);

PUBLIC BaseSerial *ArduinoCore_CreateSerial(
    BaseCore *core,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void ArduinoCore_DestroySerial(BaseCore *core, BaseSerial *serial);

PUBLIC unsigned long ArduinoCore_GetTime(BaseCore *core);
PUBLIC void ArduinoCore_Run(BaseCore *core);

// Virtual methods table(s)
static const BaseCoreVtbl baseVtbl = {
    .CreatePort = ArduinoCore_CreatePort,
    .DestroyPort = ArduinoCore_DestroyPort,
    .CreateSerial = ArduinoCore_CreateSerial,
    .DestroySerial = ArduinoCore_DestroySerial,
    .GetTime = ArduinoCore_GetTime,
    .Run = ArduinoCore_Run,
};

// Method implement(s)
PUBLIC void ArduinoCore_Construct(ArduinoCore *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(ArduinoCore));
        BaseCore_Construct(&pThis->base);
        pThis->base.vtbl = &baseVtbl;
    }
}

PUBLIC void ArduinoCore_Destruct(ArduinoCore *pThis)
{
    if (pThis != NULL) {
        BaseCore_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(ArduinoCore));
    }
}

PRIVATE ArduinoPort *ArduinoCore_AllocPort(
    ArduinoCore *pThis,
    void *port)
{
    ArduinoPort *freePort = NULL;

    if (!ArduinoPort_IsValidPort(port)) {
        return NULL;
    }

    for (unsigned int i = 0; i < ARDUINO_CORE_PORTS_NUMBER; i++) {
        ArduinoPort *cursorPort = &pThis->_ports[i];

        if (ARDUINO_PORT_IS_CONSTRUCTED(cursorPort)) {
            if (ArduinoPort_GetPort(cursorPort) == port) {
                freePort = cursorPort;
                break;
            }
        } else {
            if (freePort == NULL) {
                freePort = cursorPort;
            }
        }
    }

    return freePort;
}

PRIVATE ArduinoSerial *ArduinoCore_AllocSerial(
    ArduinoCore *pThis,
    HardwareSerial *serial)
{
    ArduinoSerial *freeSerial = NULL;

    for (unsigned int i = 0; i < ARDUINO_CORE_SERIALS_NUMBER; i++) {
        ArduinoSerial *cursorSerial = &pThis->_serials[i];

        if (ARDUINO_SERIAL_IS_CONSTRUCTED(cursorSerial)) {
            if (ArduinoSerial_GetSerial(cursorSerial) == serial) {
                freeSerial = NULL;
                break;
            }
        } else {
            if (freeSerial == NULL) {
                freeSerial = cursorSerial;
            }
        }
    }

    return freeSerial;
}

PUBLIC BasePort *ArduinoCore_CreatePort(
    BaseCore *core,
    const char *type,
    BasePortParameter *parameter)
{
    ArduinoPort *port = NULL;
    ArduinoCore *pThis = BaseCore2ArduinoCore(core);

    if (core == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, ARDUINO_CORE_ADDRESS_PORT) == 0
        || strcmp(type, ARDUINO_CORE_DIGITAL_PORT) == 0) {
        ArduinoPortParameter *arduinoParameter
            = BasePortParameter2ArduinoPortParameter(parameter);

        port = ArduinoCore_AllocPort(pThis, arduinoParameter->port);

        if (port != NULL && !ARDUINO_PORT_IS_CONSTRUCTED(port)) {
            ArduinoPort_Construct(port, arduinoParameter);
        }
    } else if (strcmp(type, GENERAL_ADDRESS_PORT) == 0
        || strcmp(type, GENERAL_DIGITAL_PORT) == 0) {
        GeneralPortParameter *generalParameter
            = BasePortParameter2GeneralPortParameter(parameter);

        ArduinoPortParameter arduinoParameter = {
            .base = ARDUINO_PORT_PARAMETER_BASE,
            .port = generalParameter->port,
        };

        port = ArduinoCore_AllocPort(pThis, generalParameter->port);

        if (port != NULL && !ARDUINO_PORT_IS_CONSTRUCTED(port)) {
            ArduinoPort_Construct(port, &arduinoParameter);
        }
    }

    return (port == NULL) ? NULL : &port->base;
}

PUBLIC void ArduinoCore_DestroyPort(BaseCore *core, BasePort *port)
{
    (void)core;
    (void)port;
}

PUBLIC BaseSerial *ArduinoCore_CreateSerial(
    BaseCore *core,
    const char *type,
    BaseSerialParameter *parameter)
{
    ArduinoSerial *serial = NULL;
    ArduinoCore *pThis = BaseCore2ArduinoCore(core);

    if (pThis == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, ARDUINO_CORE_UART_SERIAL) == 0) {
        ArduinoSerialParameter *arduinoParameter
            = BaseSerialParameter2ArduinoSerialParameter(parameter);

        serial = ArduinoCore_AllocSerial(pThis, arduinoParameter->serial);

        if (serial != NULL) {
            ArduinoSerial_Construct(serial, arduinoParameter);
        }
    } else if (strcmp(type, GENERAL_UART_SERIAL) == 0) {
        GeneralSerialParameter *generalParameter
            = BaseSerialParameter2GeneralSerialParameter(parameter);

        ArduinoSerialParameter arduinoParameter = {
            .base = ARDUINO_SERIAL_PARAMETER_BASE,
            .serial = (HardwareSerial *)generalParameter->serial,
            .baudrate = generalParameter->baudrate,
            .rxBuffer = NULL,
            .rxBufferSize = 0,
        };

        serial = ArduinoCore_AllocSerial(pThis, arduinoParameter.serial);

        if (serial != NULL) {
            ArduinoSerial_Construct(serial, &arduinoParameter);
        }
    }

    return (serial == NULL) ? NULL : &serial->base;
}

PUBLIC void ArduinoCore_DestroySerial(BaseCore *core, BaseSerial *serial)
{
    ArduinoCore *pThis = BaseCore2ArduinoCore(core);

    if (core == NULL || serial == NULL) {
        return;
    }

    for (unsigned int i = 0; i < ARDUINO_CORE_SERIALS_NUMBER; i++) {
        if (BaseSerial2ArduinoSerial(serial) == &pThis->_serials[i]) {
            ArduinoSerial_Destruct(&pThis->_serials[i]);
            break;
        }
    }
}

PUBLIC unsigned long ArduinoCore_GetTime(BaseCore *core)
{
    (void)core;
    return millis();
}

PUBLIC void ArduinoCore_Run(BaseCore *core)
{
    ArduinoCore *pThis = BaseCore2ArduinoCore(core);

    if (core == NULL) {
        return;
    }

    for (unsigned int i = 0; i < ARDUINO_CORE_SERIALS_NUMBER; i++) {
        ArduinoSerial_Sample(&pThis->_serials[i]);
    }
}
