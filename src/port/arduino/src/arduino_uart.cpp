#ifdef ARDUINO

#include "port/arduino/inc/arduino_uart.h"
#include "core/device/inc/device_manager.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Override method(s)
PUBLIC unsigned int ReadArduinoUARTBase(
    BaseSerial *serial,
    uint8_t *buffer,
    unsigned int size);

PUBLIC unsigned int WriteArduinoUARTBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    unsigned int size);

PUBLIC void SetRxCallbackToUARTBase(
    BaseSerial *serial,
    RingBufferCallback callback);

PUBLIC BaseThreadState RunArduinoUARTThreadBase(BaseThread *thread);

// Virtual methods table
static const BaseSerialVtbl serialVtbl = {
    .Read = ReadArduinoUARTBase,
    .Write = WriteArduinoUARTBase,
    .SetRxCallback = SetRxCallbackToUARTBase
};

static const BaseThreadVtbl threadVtbl = {
    .Run = RunArduinoUARTThreadBase
};

// Method implement(s)
PUBLIC void ConstructArduinoUART(
    ArduinoUART *instance,
    ArduinoUARTParameter *parameter)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL || parameter == NULL || parameter->port == NULL)
    {
        return;
    }

    ConstructBaseSerial(&instance->base, &parameter->base);
    instance->base.vtbl = &serialVtbl;

    instance->_port = parameter->port;
    instance->_port->begin(parameter->baudrate);

    if (parameter->rxBufferSize > 0)
    {
        instance->_rxBuffer = (uint8_t *)malloc(parameter->rxBufferSize);

        ConstructRingBuffer(
            &instance->_rxRingBuffer,
            instance->_rxBuffer,
            parameter->rxBufferSize);

        ConstructArduinoUARTThread(&instance->_thread, instance);

        AddThreadToDeviceManager(
            manager,
            DEVICE_MANAGER_THREAD_DRIVER_INPUT,
            &instance->_thread.base);
    }
}

PUBLIC void DestructArduinoUART(ArduinoUART *instance)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    if (instance->_rxBuffer != NULL)
    {
        RemoveThreadFromDeviceManager(
            manager,
            DEVICE_MANAGER_THREAD_DRIVER_INPUT,
            &instance->_thread.base);

        DestructArduinoUARTThread(&instance->_thread);
        DestructRingBuffer(&instance->_rxRingBuffer);
        free(instance->_rxBuffer);
    }

    instance->_port->end();
    DestructBaseSerial(&instance->base);
    memset(instance, 0, sizeof(ArduinoUART));
}

PUBLIC void ConstructArduinoUARTThread(
    ArduinoUARTThread *instance,
    ArduinoUART *uart)
{
    if (instance != NULL && uart != NULL)
    {
        ConstructBaseThread(&instance->base);
        instance->base.vtbl = &threadVtbl;
        instance->_uart = uart;
    }
}

PUBLIC void DestructArduinoUARTThread(ArduinoUARTThread *instance)
{
    if (instance != NULL)
    {
        DestructBaseThread(&instance->base);
        memset(instance, 0, sizeof(ArduinoUARTThread));
    }
}

PUBLIC unsigned int ReadArduinoUARTBase(
    BaseSerial *serial,
    uint8_t *buffer,
    unsigned int size)
{
    ArduinoUART *self = BaseSerial2ArduinoUART(serial);

    if (serial == NULL || self->_port == NULL)
    {
        return 0;
    }

    if (self->_rxBuffer != NULL)
    {
        return ReadRingBuffer(&self->_rxRingBuffer, buffer, size);
    }

    return self->_port->readBytes(buffer, size);
}

PUBLIC unsigned int WriteArduinoUARTBase(
    BaseSerial *serial,
    const uint8_t *buffer,
    unsigned int size)
{
    ArduinoUART *self = BaseSerial2ArduinoUART(serial);

    if (serial == NULL || self->_port == NULL)
    {
        return 0;
    }

    return self->_port->write(buffer, size);
}

PUBLIC void SetRxCallbackToUARTBase(
    BaseSerial *serial,
    RingBufferCallback callback)
{
    ArduinoUART *self = BaseSerial2ArduinoUART(serial);

    if (serial != NULL)
    {
        SetCallbackToRingBuffer(&self->_rxRingBuffer, callback);
    }
}

PUBLIC BaseThreadState RunArduinoUARTThreadBase(BaseThread *thread)
{
    uint8_t data = 0;
    ArduinoUARTThread *self = BaseThread2ArduinoUARTThread(thread);

    if (thread == NULL)
    {
        return BASE_THREAD_STATE_ENDED;
    }

    BEGIN_BASE_THREAD(thread);

    for (;;)
    {
        if (self->_uart->_port->available() > 0)
        {
            data = (uint8_t)self->_uart->_port->read();
            WriteRingBuffer(&self->_uart->_rxRingBuffer, &data, 1);
        }

        YIELD_BASE_THREAD(thread);
    }

    END_BASE_THREAD(thread);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARDUINO
