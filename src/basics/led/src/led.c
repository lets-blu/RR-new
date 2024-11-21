#include "basics/led/inc/led.h"

// Private member(s)
PRIVATE STATIC Logger logger = STATIC_LOGGER("LED", LOGGER_LEVEL_INFO);

// Method implement(s)
PUBLIC void ConstructLED(
    LED *instance,
    void *port,
    unsigned int pin,
    unsigned int onValue)
{
    GeneralPortParameter parameter = {
        .base   = GENERAL_PORT_PARAMETER_BASE,
        .port   = port,
        .pin    = pin
    };

    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    RegisterLogger(&logger);

    instance->_port = CreatePortWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        GENERAL_DIGITAL_PORT,
        &parameter.base);

    instance->_pin = pin;
    instance->_onValue = onValue;
    SetupBasePort(instance->_port, pin, BASE_PORT_MODE_OUTPUT);
}

PUBLIC void DestructLED(LED *instance)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    DestroyPortWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        GENERAL_DIGITAL_PORT,
        instance->_port);

    memset(instance, 0, sizeof(LED));
}

PUBLIC void TurnOnLED(LED *self)
{
    if (self == NULL)
    {
        return;
    }

    LOGGER_I(&logger, "Turn on  %p", self);

    if (self->_onValue == BASE_PORT_VALUE_LOW)
    {
        WriteBasePort(self->_port, self->_pin, BASE_PORT_VALUE_LOW);
    }
    else
    {
        WriteBasePort(self->_port, self->_pin, BASE_PORT_VALUE_HIGH);
    }
}

PUBLIC void TurnOffLED(LED *self)
{
    if (self == NULL)
    {
        return;
    }

    LOGGER_I(&logger, "Turn off %p", self);

    if (self->_onValue == BASE_PORT_VALUE_LOW)
    {
        WriteBasePort(self->_port, self->_pin, BASE_PORT_VALUE_HIGH);
    }
    else
    {
        WriteBasePort(self->_port, self->_pin, BASE_PORT_VALUE_LOW);
    }
}
