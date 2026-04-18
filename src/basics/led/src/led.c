#include "basics/led/inc/led.h"

// Private member(s)
PRIVATE STATIC Logger logger = LOGGER_STATIC("LED", LOGGER_LEVEL_INFO);

// Method implement(s)
PUBLIC void LED_Construct(
    LED *pThis,
    void *port,
    unsigned int pin,
    unsigned int onValue)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = port,
    };

    if (pThis == NULL) {
        return;
    }

    Logger_Register(&logger);

    pThis->_port = DeviceFactory_CreatePort(
        DeviceFactory_GetInstance(),
        GENERAL_DIGITAL_PORT,
        &parameter.base);

    pThis->_pin = pin;
    pThis->_onValue = onValue;
    BasePort_SetMode(pThis->_port, pin, BASE_PORT_MODE_OUTPUT);
}

PUBLIC void LED_Destruct(LED *pThis)
{
    if (pThis != NULL) {
        DeviceFactory_DestroyPort(DeviceFactory_GetInstance(), pThis->_port);
        memset(pThis, 0, sizeof(LED));
    }
}

PUBLIC void LED_TurnOn(LED *pThis)
{
    if (pThis != NULL) {
        LOGGER_D(&logger, "Turn on  %p", pThis);
        BasePort_Write(pThis->_port, pThis->_pin, pThis->_onValue);
    }
}

PUBLIC void LED_TurnOff(LED *pThis)
{
    if (pThis == NULL) {
        return;
    }

    LOGGER_D(&logger, "Turn off %p", pThis);

    if (pThis->_onValue == BASE_PORT_VALUE_LOW) {
        BasePort_Write(pThis->_port, pThis->_pin, BASE_PORT_VALUE_HIGH);
    } else {
        BasePort_Write(pThis->_port, pThis->_pin, BASE_PORT_VALUE_LOW);
    }
}
