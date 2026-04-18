#include "port/arduino/inc/arduino_serial.h"

// Override method(s)
PUBLIC size_t ArduinoSerial_Read(
    BaseSerial *serial,
    uint8_t *buffer,
    size_t bufferSize);

PUBLIC size_t ArduinoSerial_Write(
    BaseSerial *serial,
    const uint8_t *buffer,
    size_t bufferLength);

PUBLIC void ArduinoSerial_SetEventHandler(
    BaseSerial *serial,
    EventHandler handler);

// Virtual methods table(s)
static const BaseSerialVtbl baseVtbl = {
    .Read = ArduinoSerial_Read,
    .Write = ArduinoSerial_Write,
    .SetEventHandler = ArduinoSerial_SetEventHandler,
};

// Method implement(s)
PUBLIC void ArduinoSerial_Construct(
    ArduinoSerial *pThis,
    ArduinoSerialParameter *parameter)
{
    if (pThis == NULL || parameter == NULL || parameter->serial == NULL) {
        return;
    }

    BaseSerial_Construct(&pThis->base, &parameter->base);
    pThis->base.vtbl = &baseVtbl;

    pThis->_serial = parameter->serial;
    pThis->_serial->begin(parameter->baudrate);

    if (parameter->rxBuffer != NULL && parameter->rxBufferSize != 0) {
        RingBuffer_Construct(
            &pThis->_rxBuffer,
            parameter->rxBuffer,
            parameter->rxBufferSize);
    }

    pThis->_handler = NULL;
}

PUBLIC void ArduinoSerial_Destruct(ArduinoSerial *pThis)
{
    if (pThis != NULL) {
        RingBuffer_Destruct(&pThis->_rxBuffer);
        BaseSerial_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(ArduinoSerial));
    }
}

PUBLIC void ArduinoSerial_Sample(ArduinoSerial *pThis)
{
    int available = 0;

    if (pThis == NULL || pThis->_serial == NULL) {
        return;
    }

    available = pThis->_serial->available();

    if (RING_BUFFER_IS_CONSTRUCTED(&pThis->_rxBuffer) && available > 0) {
        uint8_t buffer[ARDUINO_SERIAL_BUFFER_SIZE] = {0};

        if (available > ARDUINO_SERIAL_BUFFER_SIZE) {
            available = ARDUINO_SERIAL_BUFFER_SIZE;
        }

        pThis->_serial->readBytes(buffer, available);
        RingBuffer_Write(&pThis->_rxBuffer, buffer, available);

        if (pThis->_handler != NULL) {
            BaseSerialEventArgs args = {
                .base = BASE_SERIAL_EVENT_ARGS_BASE,
                .event = BASE_SERIAL_EVENT_DATA_RECEIVED,
                .buffer = &pThis->_rxBuffer,
            };

            pThis->_handler(pThis, &args.base);
        }
    }
}

PUBLIC HardwareSerial *ArduinoSerial_GetSerial(ArduinoSerial *pThis)
{
    return (pThis == NULL) ? NULL : pThis->_serial;
}

PUBLIC size_t ArduinoSerial_Read(
    BaseSerial *serial,
    uint8_t *buffer,
    size_t bufferSize)
{
    ArduinoSerial *pThis = BaseSerial2ArduinoSerial(serial);

    if (serial == NULL || pThis->_serial == NULL) {
        return 0;
    }

    if (RING_BUFFER_IS_CONSTRUCTED(&pThis->_rxBuffer)) {
        return RingBuffer_Read(&pThis->_rxBuffer, buffer, bufferSize);
    }

    return pThis->_serial->readBytes(buffer, bufferSize);
}

PUBLIC size_t ArduinoSerial_Write(
    BaseSerial *serial,
    const uint8_t *buffer,
    size_t bufferLength)
{
    ArduinoSerial *pThis = BaseSerial2ArduinoSerial(serial);

    if (serial == NULL || pThis->_serial == NULL) {
        return 0;
    }

    return pThis->_serial->write(buffer, bufferLength);
}

PUBLIC void ArduinoSerial_SetEventHandler(
    BaseSerial *serial,
    EventHandler handler)
{
    ArduinoSerial *pThis = BaseSerial2ArduinoSerial(serial);

    if (serial != NULL) {
        pThis->_handler = handler;
    }
}
