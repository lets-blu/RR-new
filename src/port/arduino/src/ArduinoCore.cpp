#ifdef ARDUINO

#include "port/arduino/inc/ArduinoCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC const char *GetNameOfArduinoCoreBase(
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
    .GetName = GetNameOfArduinoCoreBase
};

static const BaseFactoryVtbl baseFactoryVtbl = {
    .CreatePort = CreatePortWithArduinoCoreBase,
    .DestroyPort = DestroyPortWithArduinoCoreBase
};

// Method implement(s)
PUBLIC void ConstructArduinoCore(ArduinoCore *instance)
{
    if (instance != NULL)
    {
        ConstructBaseCore(&instance->base);
        instance->base.vtbl = &baseCoreVtbl;
        instance->base.base.vtbl = &baseFactoryVtbl;
    }
}

PUBLIC void DestructArduinoCore(ArduinoCore *instance)
{
    if (instance != NULL)
    {
        DestructBaseCore(&instance->base);
        memset(instance, 0, sizeof(ArduinoCore));
    }
}

PUBLIC const char *GetNameOfArduinoCoreBase(
    BaseCore *core)
{
    (void)core;
    return "Arduino";
}

PUBLIC BasePort *CreatePortWithArduinoCoreBase(
    BaseFactory *factory, 
    const char *type,
    BasePortParameter *parameter)
{
    (void)factory;
    BasePort *port = NULL;

    if (type == NULL)
    {
        return NULL;
    }

    if (strcmp(type, ARDUINO_CORE_DIGITAL_PORT) == 0
        || strcmp(type, BASE_FACTORY_DIGITAL_PORT) == 0)
    {
        port = (BasePort *)malloc(sizeof(ArduinoDPort));

        if (port != NULL)
        {
            ConstructArduinoDPort(
                BasePort2ArduinoDPort(port),
                BasePortParameter2ArduinoDPortParameter(parameter));
        }
    }

    return port;
}

PUBLIC void DestroyPortWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port)
{
    (void)factory;
    
    if (type == NULL)
    {
        return;
    }

    if (strcmp(type, ARDUINO_CORE_DIGITAL_PORT) == 0
        || strcmp(type, BASE_FACTORY_DIGITAL_PORT) == 0)
    {
        DestructArduinoDPort(BasePort2ArduinoDPort(port));
        free(port);
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
