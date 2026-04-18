#include "digital/register/inc/register_port.h"
#include "digital/register/inc/register_group.h"

// Override method(s)
PUBLIC void RegisterPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode);

PUBLIC unsigned int RegisterPort_Read(
    BasePort *port,
    unsigned int pin);

PUBLIC void RegisterPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value);

// Virtual methods table(s)
static const BasePortVtbl baseVtbl = {
    .SetMode = RegisterPort_SetMode,
    .Read = RegisterPort_Read,
    .Write = RegisterPort_Write,
};

// Method implement(s)
PUBLIC void RegisterPort_Construct(
    RegisterPort *pThis,
    RegisterPortParameter *parameter)
{
    if (pThis != NULL && parameter != NULL) {
        BasePort_Construct(&pThis->base, &parameter->base);
        pThis->base.vtbl = &baseVtbl;
        pThis->_group = parameter->group;
    }
}

PUBLIC void RegisterPort_Destruct(RegisterPort *pThis)
{
    if (pThis != NULL) {
        BasePort_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(RegisterPort));
    }
}

PUBLIC void RegisterPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode)
{
    (void)port;
    (void)pin;
    (void)mode;
}

PUBLIC unsigned int RegisterPort_Read(
    BasePort *port,
    unsigned int pin)
{
    (void)port;
    (void)pin;
    return 0;
}

PUBLIC void RegisterPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value)
{
    RegisterPort *pThis = BasePort2RegisterPort(port);

    if (port == NULL) {
        return;
    }

    if (value == BASE_PORT_VALUE_LOW) {
        RegisterGroup_ResetBit(pThis->_group, pin);
    } else {
        RegisterGroup_SetBit(pThis->_group, pin);
    }
}
