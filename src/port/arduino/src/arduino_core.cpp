#ifdef ARDUINO

#include <Arduino.h>
#include "port/arduino/inc/arduino_core.h"
#include "core/device/inc/device_manager.h"

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

PUBLIC BaseThreadState RunArduinoCoreThreadBase(
    BaseThread *thread);

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

static const BaseThreadVtbl baseThreadVtbl = {
    .Run = RunArduinoCoreThreadBase
};

// Method implement(s)
PUBLIC void ConstructArduinoCore(ArduinoCore *instance)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    ConstructBaseCore(&instance->base);
    instance->base.vtbl = &baseCoreVtbl;
    instance->base.base.vtbl = &baseFactoryVtbl;

    ConstructArduinoCoreThread(
        &instance->_thread,
        instance);

    AddThreadToDeviceManager(
        manager,
        DEVICE_MANAGER_THREAD_DRIVER_INPUT,
        &instance->_thread.base);
}

PUBLIC void DestructArduinoCore(ArduinoCore *instance)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    RemoveThreadFromDeviceManager(
        manager,
        DEVICE_MANAGER_THREAD_DRIVER_INPUT,
        &instance->_thread.base);

    DestructArduinoCoreThread(&instance->_thread);
    DestructBaseCore(&instance->base);
    memset(instance, 0, sizeof(ArduinoCore));
}

PUBLIC void ConstructArduinoCoreThread(
    ArduinoCoreThread *instance,
    ArduinoCore *core)
{
    if (instance != NULL)
    {
        ConstructBaseThread(&instance->base);
        instance->base.vtbl = &baseThreadVtbl;
        instance->_core = core;
    }
}

PUBLIC void DestructArduinoCoreThread(ArduinoCoreThread *instance)
{
    if (instance != NULL)
    {
        DestructBaseThread(&instance->base);
        memset(instance, 0, sizeof(ArduinoCoreThread));
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
        if (!IS_ARDUINO_DIGITAL_PORT_CONSTRUCTED(&self->_digitalPort))
        {
            ConstructArduinoDigitalPort(
                &self->_digitalPort,
                BasePortParameter2ArduinoDigitalPortParameter(parameter));
        }

        port = &self->_digitalPort.base;
    }
    else if (strcmp(type, GENERAL_DIGITAL_PORT) == 0)
    {
        GeneralPortParameter *generalParameter
            = BasePortParameter2GeneralPortParameter(parameter);

        ArduinoDigitalPortParameter arduinoParameter = {
            .base = ARDUINO_DIGITAL_PORT_PARAMETER_BASE
        };

        if (generalParameter->port != NULL)
        {
            return NULL;
        }

        if (!IS_ARDUINO_DIGITAL_PORT_CONSTRUCTED(&self->_digitalPort))
        {
            ConstructArduinoDigitalPort(&self->_digitalPort, &arduinoParameter);
        }

        port = &self->_digitalPort.base;
    }

    return port;
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
        if (!IS_ARDUINO_UART_SERIAL_CONSTRUCTED(&self->_uartSerial))
        {
            ConstructArduinoUARTSerial(
                &self->_uartSerial,
                BaseSerialParameter2ArduinoUARTSerialParameter(parameter));
        }

        serial = &self->_uartSerial.base;
    }
    else if (strcmp(type, GENERAL_UART_SERIAL) == 0)
    {
        GeneralUARTSerialParameter *generalParameter
            = BaseSerialParameter2GeneralUARTSerialParameter(parameter);

        ArduinoUARTSerialParameter arduinoParameter = {
            .base = ARDUINO_UART_SERIAL_PARAMETER_BASE,
            .baudrate = generalParameter->baudrate,
            .buffer = NULL
        };

        if (generalParameter->port != &Serial)
        {
            return NULL;
        }

        if (!IS_ARDUINO_UART_SERIAL_CONSTRUCTED(&self->_uartSerial))
        {
            ConstructArduinoUARTSerial(&self->_uartSerial, &arduinoParameter);
        }

        serial = &self->_uartSerial.base;
    }

    return serial;
}

PUBLIC void DestroySerialWithArduinoCoreBase(
    BaseFactory *factory,
    const char *type,
    BaseSerial *serial)
{
    (void)factory;
    (void)type;
    (void)serial;
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

PUBLIC BaseThreadState RunArduinoCoreThreadBase(
    BaseThread *thread)
{
    ArduinoCore *core = NULL;
    ArduinoCoreThread *self = BaseThread2ArduinoCoreThread(thread);

    if (self == NULL)
    {
        return BASE_THREAD_STATE_ENDED;
    }

    core = self->_core;
    BEGIN_BASE_THREAD(thread);

    for (;;)
    {
        if (IS_ARDUINO_UART_SERIAL_CONSTRUCTED(&core->_uartSerial))
        {
            SampleBaseSerial(&core->_uartSerial.base);
        }

        YIELD_BASE_THREAD(thread);
    }

    END_BASE_THREAD(thread);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
