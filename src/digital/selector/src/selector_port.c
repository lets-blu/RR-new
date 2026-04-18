#include "digital/selector/inc/selector_port.h"
#include "digital/selector/inc/selector_group.h"

// Override method(s)
PUBLIC void SelectorPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode);

PUBLIC unsigned int SelectorPort_Read(
    BasePort *port,
    unsigned int pin);

PUBLIC void SelectorPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value);

// Virtual methods table(s)
static const BasePortVtbl baseVtbl = {
    .SetMode = SelectorPort_SetMode,
    .Read = SelectorPort_Read,
    .Write = SelectorPort_Write,
};

// Method implement(s)
PUBLIC void SelectorPort_Construct(
    SelectorPort *pThis,
    SelectorPortParameter *parameter)
{
    if (pThis != NULL && parameter != NULL) {
        BasePort_Construct(&pThis->base, &parameter->base);
        pThis->base.vtbl = &baseVtbl;
        pThis->_group = parameter->group;
    }
}

PUBLIC void SelectorPort_Destruct(SelectorPort *pThis)
{
    if (pThis != NULL) {
        BasePort_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(SelectorPort));
    }
}

PUBLIC void SelectorPort_SetMode(
    BasePort *port,
    unsigned int pin,
    BasePortMode mode)
{
    (void)port;
    (void)pin;
    (void)mode;
}

PUBLIC unsigned int SelectorPort_Read(
    BasePort *port,
    unsigned int pin)
{
    SelectorPort *pThis = BasePort2SelectorPort(port);

    if (port == NULL) {
        return 0;
    }

    return SelectorGroup_GetBit(pThis->_group, pin);
}

PUBLIC void SelectorPort_Write(
    BasePort *port,
    unsigned int pin,
    unsigned int value)
{
    (void)port;
    (void)pin;
    (void)value;
}
