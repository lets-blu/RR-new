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
    ConstructLinkedList(&instance->_digitalPorts);
}

PUBLIC void DestructArduinoCore(ArduinoCore *instance)
{
    if (instance == NULL)
    {
        return;
    }

    DestructLinkedList(&instance->_digitalPorts);
    DestructLinkedList(&instance->_devices);
    DestructBaseCore(&instance->base);

    memset(instance, 0, sizeof(ArduinoCore));
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
    uint8_t *port = NULL;
    LinkedListNode *node = NULL;
    ArduinoDigitalPort *digitalPort = NULL;

    ArduinoCore *self = BaseFactory2ArduinoCore(factory);

    // 1. Check parameter(s)
    if (factory == NULL || type == NULL || parameter == NULL)
    {
        return NULL;
    }

    // 2. Check type
    if (strcmp(type, GENERAL_DIGITAL_PORT) == 0)
    {
        port = (uint8_t *)BasePortParameter2GeneralPortParameter(
            parameter)->port;
    }
    else if (strcmp(type, ARDUINO_CORE_DIGITAL_PORT) == 0)
    {
        port = BasePortParameter2ArduinoDigitalPortParameter(parameter)->port;
    }
    else
    {
        return NULL;
    }

    // 3. Check if port is already created
    node = FindNodeInLinkedList(
        &self->_digitalPorts,
        FindCallbackOfArduinoDigitalPort,
        port);

    if (node != NULL)
    {
        return LinkedListNode2BasePort(node);
    }

    // 4. Create port
    digitalPort = InstanceOfArduinoDigitalPort(port);
    AddNodeToLinkedList(&self->_digitalPorts, &digitalPort->base.base);

    return &digitalPort->base;
}

PUBLIC void DestroyPortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port)
{
    (void)factory;
    (void)type;
    (void)port;
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

        if (serial == NULL)
        {
            return NULL;
        }

        ConstructArduinoUART(
            BaseSerial2ArduinoUART(serial),
            BaseSerialParameter2ArduinoUARTParameter(parameter));

        AddNodeToLinkedList(&self->_devices, &serial->base);
    }
    else if (strcmp(type, GENERAL_UART_SERIAL) == 0)
    {
        GeneralUARTParameter *generalParameter
            = BaseSerialParameter2GeneralUARTParameter(parameter);

        ArduinoUARTParameter arduinoParameter = {
            .base = ARDUINO_UART_PARAMETER_BASE,
            .port = (HardwareSerial *)generalParameter->port,
            .baudrate = generalParameter->baudrate,
            .rxBufferSize = 0
        };

        serial = (BaseSerial *)malloc(sizeof(ArduinoUART));

        if (serial == NULL)
        {
            return NULL;
        }

        ConstructArduinoUART(BaseSerial2ArduinoUART(serial), &arduinoParameter);
        AddNodeToLinkedList(&self->_devices, &serial->base);
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
