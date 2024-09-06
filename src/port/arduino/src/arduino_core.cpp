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

// Virtual methods table
static const BaseCoreVtbl baseCoreVtbl = {
    .GetName = GetNameOfArduinoCoreBase,
    .GetTick = GetTickOfArduinoCoreBase
};

static const BaseFactoryVtbl baseFactoryVtbl = {
    .CreatePort = CreatePortWithArduinoCoreBase,
    .DestroyPort = DestroyPortWithArduinoCoreBase,
    .CreateTask = NULL,
    .DestroyTask = NULL
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

    ConstructLinkedList(&instance->_ports);
}

PUBLIC void DestructArduinoCore(ArduinoCore *instance)
{
    if (instance != NULL)
    {
        DestructBaseCore(&instance->base);
        DestructLinkedList(&instance->_ports);
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

            AddNodeToLinkedList(&self->_ports, &port->base);
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

            AddNodeToLinkedList(&self->_ports, &port->base);
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
            &self->_ports,
            FindEqualCallbackOfLinkedList,
            &port->base) != NULL)
    {
        RemoveNodeFromLinkedList(&self->_ports, &port->base);
        DestructArduinoDPort(BasePort2ArduinoDPort(port));
        free(port);
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
