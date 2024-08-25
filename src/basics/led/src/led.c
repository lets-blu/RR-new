#include "basics/led/inc/led.h"

// Method implement(s)
PUBLIC void ConstructLED(
    LED *instance,
    BasePortParameter *parameter,
    unsigned int onValue)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    instance->_port = CreatePortWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        BASE_FACTORY_DIGITAL_PORT,
        parameter);
    
    instance->_onValue = onValue;

    SetupBasePort(instance->_port, BASE_PORT_MODE_OUTPUT);
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
        BASE_FACTORY_DIGITAL_PORT,
        instance->_port);
    
    memset(instance, 0, sizeof(LED));
}

PUBLIC void TurnOnLED(LED *self)
{
    if (self == NULL)
    {
        return;
    }

    printf("[LED][I] Turn on  %p\r\n", self);

    if (self->_onValue == BASE_PORT_VALUE_LOW)
    {
        WriteBasePort(self->_port, BASE_PORT_VALUE_LOW);
    }
    else
    {
        WriteBasePort(self->_port, BASE_PORT_VALUE_HIGH);
    }
}

PUBLIC void TurnOffLED(LED *self)
{
    if (self == NULL)
    {
        return;
    }

    printf("[LED][I] Turn off %p\r\n", self);

    if (self->_onValue == BASE_PORT_VALUE_LOW)
    {
        WriteBasePort(self->_port, BASE_PORT_VALUE_HIGH);
    }
    else
    {
        WriteBasePort(self->_port, BASE_PORT_VALUE_LOW);
    }
}
