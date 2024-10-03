#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/arduino_core.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC const char *GetNameOfArduinoCoreBase(
    BaseCore *core);

PUBLIC unsigned long GetTickOfArduinoCoreBase(
    BaseCore *core);

PUBLIC BasePort *CreatePortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void DestroyPortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port);

PUBLIC BaseSerial *CreateSerialWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void DestroySerialWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseSerial *serial);

PUBLIC BaseTask *CreateTaskWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void DestroyTaskWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseTask *task);

// Virtual methods table
static const BaseCoreVtbl baseCoreVtbl = {
    .GetName = GetNameOfArduinoCoreBase,
    .GetTick = GetTickOfArduinoCoreBase
};

static const BaseFactoryVtbl baseFactoryVtbl = {
    .CreatePort     = CreatePortWithArduinoCoreBase,
    .DestroyPort    = DestroyPortWithArduinoCoreBase,
    .CreateSerial   = CreateSerialWithArduinoCoreBase,
    .DestroySerial  = DestroySerialWithArduinoCoreBase,
    .CreateTask     = CreateTaskWithArduinoCoreBase,
    .DestroyTask    = DestroyTaskWithArduinoCoreBase
};

// Method implement(s)
PUBLIC void ConstructArduinoCore(ArduinoCore *instance)
{
    if (instance == NULL)
    {
        return;
    }

    ConstructBaseCore(&instance->base);
    instance->base.vtbl = &baseCoreVtbl;
    instance->base.base.vtbl = &baseFactoryVtbl;

    ConstructLinkedList(&instance->_devices);
}

PUBLIC void DestructArduinoCore(ArduinoCore *instance)
{
    if (instance != NULL)
    {
        DestructBaseCore(&instance->base);
        DestructLinkedList(&instance->_devices);
        memset(instance, 0, sizeof(ArduinoCore));
    }
}

PUBLIC const char *GetNameOfArduinoCoreBase(
    BaseCore *core)
{
    (void)core;
    return "Arduino";
}

PUBLIC unsigned long GetTickOfArduinoCoreBase(
    BaseCore *core)
{
    (void)core;
    return millis();
}

PUBLIC BasePort *CreatePortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePortParameter *parameter)
{
    BasePort *port = NULL;
    ArduinoCore *self = BaseFactory2ArduinoCore(factory);

    if (factory == NULL || type == NULL || parameter == NULL)
    {
        return NULL;
    }

    if (strcmp(type, ARDUINO_CORE_DIGITAL_PORT) == 0)
    {
        port = (BasePort *)malloc(sizeof(ArduinoDPort));

        if (port != NULL)
        {
            ConstructArduinoDPort(
                BasePort2ArduinoDPort(port),
                BasePortParameter2ArduinoDPortParameter(parameter));

            AddNodeToLinkedList(&self->_devices, &port->base);
        }
    }
    else if (strcmp(type, GENERAL_DIGITAL_PORT) == 0)
    {
        GeneralPortParameter *generalParameter
            = BasePortParameter2GeneralPortParameter(parameter);

        ArduinoDPortParameter arduinoParameter = {
            .base = ARDUINO_D_PORT_PARAMETER_BASE,
            .pin = (uint8_t)generalParameter->pin
        };

        port = (BasePort *)malloc(sizeof(ArduinoDPort));

        if (port != NULL)
        {
            ConstructArduinoDPort(
                BasePort2ArduinoDPort(port),
                &arduinoParameter);

            AddNodeToLinkedList(&self->_devices, &port->base);
        }
    }

    return port;
}

PUBLIC void DestroyPortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port)
{
    (void)type;
    ArduinoCore *self = BaseFactory2ArduinoCore(factory);

    if (factory == NULL || port == NULL)
    {
        return;
    }

    if (FindNodeInLinkedList(
            &self->_devices,
            FindEqualCallbackOfLinkedList,
            &port->base) != NULL)
    {
        RemoveNodeFromLinkedList(&self->_devices, &port->base);
        DestructArduinoDPort(BasePort2ArduinoDPort(port));
        free(port);
    }
}

PUBLIC BaseSerial *CreateSerialWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseSerialParameter *parameter)
{
    BaseSerial *serial = NULL;
    ArduinoCore *self = BaseFactory2ArduinoCore(factory);

    if (factory == NULL || type == NULL || parameter == NULL)
    {
        return NULL;
    }

    if (strcmp(type, ARDUINO_CORE_UART_SERIAL) == 0)
    {
        serial = (BaseSerial *)malloc(sizeof(ArduinoUART));

        if (serial != NULL)
        {
            ConstructArduinoUART(
                BaseSerial2ArduinoUART(serial),
                BaseSerialParameter2ArduinoUARTParameter(parameter));

            AddNodeToLinkedList(&self->_devices, &serial->base);
        }
    }
    else if (strcmp(type, GENERAL_UART_SERIAL) == 0)
    {
        GeneralUARTParameter *generalParameter
            = BaseSerialParameter2GeneralUARTParameter(parameter);

        ArduinoUARTParameter arduinoParameter = {
            .base = ARDUINO_UART_PARAMETER_BASE,
            .port = (HardwareSerial *)generalParameter->port,
            .baudrate = generalParameter->baudrate
        };

        serial = (BaseSerial *)malloc(sizeof(ArduinoUART));

        if (serial != NULL)
        {
            ConstructArduinoUART(
                BaseSerial2ArduinoUART(serial),
                &arduinoParameter);

            AddNodeToLinkedList(&self->_devices, &serial->base);
        }
    }

    return serial;
}

PUBLIC void DestroySerialWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseSerial *serial)
{
    (void)type;
    ArduinoCore *self = (ArduinoCore *)factory;

    if (factory == NULL || serial == NULL)
    {
        return;
    }

    if (FindNodeInLinkedList(
            &self->_devices,
            FindEqualCallbackOfLinkedList,
            &serial->base) != NULL)
    {
        RemoveNodeFromLinkedList(&self->_devices, &serial->base);
        DestructArduinoUART(BaseSerial2ArduinoUART(serial));
        free(serial);
    }
}

PUBLIC BaseTask *CreateTaskWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseTaskParameter *parameter)
{
    (void)factory;
    (void)type;
    (void)parameter;

    return NULL;
}

PUBLIC void DestroyTaskWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseTask *task)
{
    (void)factory;
    (void)type;
    (void)task;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
