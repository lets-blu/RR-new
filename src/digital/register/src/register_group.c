#include "digital/register/inc/register_group.h"

// Private method(s)
PRIVATE void RegisterGroup_Refresh(RegisterGroup *pThis);

PRIVATE void RegisterGroup_RefreshRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister);

// Override method(s)
PUBLIC BasePort *RegisterGroup_CreatePort(
    BaseComponent *component,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void RegisterGroup_DestroyPort(BaseComponent *component, BasePort *port);

// Virtual methods table(s)
static const BaseComponentVtbl baseVtbl = {
    .CreatePort = RegisterGroup_CreatePort,
    .DestroyPort = RegisterGroup_DestroyPort,
};

// Method implement(s)
PUBLIC void RegisterGroup_Construct(
    RegisterGroup *pThis,
    RegisterGroupParameter *parameter)
{
    GeneralPortParameter portParameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
    };

    if (pThis == NULL || parameter == NULL) {
        return;
    }

    BaseComponent_Construct(&pThis->base);
    pThis->base.vtbl = &baseVtbl;

    LinkedList_Construct(&pThis->_registers);
    pThis->_registersNumber = 0;

    portParameter.port = parameter->port;

    pThis->_port = DeviceFactory_CreatePort(
        DeviceFactory_GetInstance(),
        GENERAL_DIGITAL_PORT,
        &portParameter.base);

    pThis->_serPin = parameter->serPin;
    BasePort_SetMode(pThis->_port, pThis->_serPin, BASE_PORT_MODE_OUTPUT);
    pThis->_sckPin = parameter->sckPin;
    BasePort_SetMode(pThis->_port, pThis->_sckPin, BASE_PORT_MODE_OUTPUT);
    pThis->_rckPin = parameter->rckPin;
    BasePort_SetMode(pThis->_port, pThis->_rckPin, BASE_PORT_MODE_OUTPUT);
}

PUBLIC void RegisterGroup_Destruct(RegisterGroup *pThis)
{
    if (pThis == NULL) {
        return;
    }

    BaseComponent_Destruct(&pThis->base);
    LinkedList_Destruct(&pThis->_registers);
    DeviceFactory_DestroyPort(DeviceFactory_GetInstance(), pThis->_port);

    memset(pThis, 0, sizeof(RegisterGroup));
}

PUBLIC void RegisterGroup_AddRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister)
{
    if (pThis != NULL && pRegister != NULL) {
        LinkedList_AddHead(&pThis->_registers, &pRegister->base);
        pThis->_registersNumber++;
    }
}

PUBLIC void RegisterGroup_RemoveRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister)
{
    if (pThis != NULL && pRegister != NULL) {
        LinkedList_RemoveNode(&pThis->_registers, &pRegister->base);
        pThis->_registersNumber--;
    }
}

PUBLIC void RegisterGroup_SetBit(RegisterGroup *pThis, unsigned int bit)
{
    ShiftRegister *pRegister = NULL;
    unsigned int index = bit / SHIFT_REGISTER_DATA_BITS;

    if (pThis == NULL && index < pThis->_registersNumber) {
        return;
    }

    pRegister = LinkedListNode2ShiftRegister(
        LinkedList_GetHead(&pThis->_registers));

    index = pThis->_registersNumber - index - 1;

    for (unsigned int i = 0; i < index && pRegister != NULL; i++) {
        pRegister = LinkedListNode2ShiftRegister(
            LinkedListNode_GetNext(&pRegister->base));
    }

    if (pRegister != NULL) {
        ShiftRegister_SetBit(pRegister, bit % SHIFT_REGISTER_DATA_BITS);
        RegisterGroup_Refresh(pThis);
    }
}

PUBLIC void RegisterGroup_ResetBit(RegisterGroup *pThis, unsigned int bit)
{
    ShiftRegister *pRegister = NULL;
    unsigned int index = bit / SHIFT_REGISTER_DATA_BITS;

    if (pThis == NULL && index < pThis->_registersNumber) {
        return;
    }

    pRegister = LinkedListNode2ShiftRegister(
        LinkedList_GetHead(&pThis->_registers));

    index = pThis->_registersNumber - index - 1;

    for (unsigned int i = 0; i < index && pRegister != NULL; i++) {
        pRegister = LinkedListNode2ShiftRegister(
            LinkedListNode_GetNext(&pRegister->base));
    }

    if (pRegister != NULL) {
        ShiftRegister_ResetBit(pRegister, bit % SHIFT_REGISTER_DATA_BITS);
        RegisterGroup_Refresh(pThis);
    }
}

PRIVATE void RegisterGroup_Refresh(RegisterGroup *pThis)
{
    LinkedListIterator iterator;
    LinkedListIterator_Construct(&iterator, &pThis->_registers);

    while (LinkedListIterator_HasNext(&iterator)) {
        ShiftRegister *pRegister = LinkedListNode2ShiftRegister(
            LinkedListIterator_GetNext(&iterator));

        RegisterGroup_RefreshRegister(pThis, pRegister);
    }

    BasePort_Write(pThis->_port, pThis->_rckPin, BASE_PORT_VALUE_HIGH);
    BasePort_Write(pThis->_port, pThis->_rckPin, BASE_PORT_VALUE_LOW);
    LinkedListIterator_Destruct(&iterator);
}

PRIVATE void RegisterGroup_RefreshRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister)
{
    uint8_t data = ShiftRegister_GetData(pRegister);

    for (unsigned int i = 0; i < SHIFT_REGISTER_DATA_BITS; i++) {
        if ((data & (1 << (SHIFT_REGISTER_DATA_BITS - 1))) != 0) {
            BasePort_Write(pThis->_port, pThis->_serPin, BASE_PORT_VALUE_HIGH);
        } else {
            BasePort_Write(pThis->_port, pThis->_serPin, BASE_PORT_VALUE_LOW);
        }

        data <<= 1;
        BasePort_Write(pThis->_port, pThis->_sckPin, BASE_PORT_VALUE_HIGH);
        BasePort_Write(pThis->_port, pThis->_sckPin, BASE_PORT_VALUE_LOW);
    }
}

PUBLIC BasePort *RegisterGroup_CreatePort(
    BaseComponent *component,
    const char *type,
    BasePortParameter *parameter)
{
    RegisterGroup *pThis = BaseComponent2RegisterGroup(component);

    if (component == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, REGISTER_GROUP_DIGITAL_PORT) == 0) {
        RegisterPortParameter *registerParameter
            = BasePortParameter2RegisterPortParameter(parameter);

        if (registerParameter->group != pThis) {
            return NULL;
        }

        if (!REGISTER_PORT_IS_CONSTRUCTED(&pThis->_vPort)) {
            RegisterPort_Construct(&pThis->_vPort, registerParameter);
        }
    } else if (strcmp(type, GENERAL_DIGITAL_PORT) == 0) {
        GeneralPortParameter *generalParameter
            = BasePortParameter2GeneralPortParameter(parameter);

        RegisterPortParameter registerParameter = {
            .base = REGISTER_PORT_PARAMETER_BASE,
            .group = pThis,
        };

        if (generalParameter->port != pThis) {
            return NULL;
        }

        if (!REGISTER_PORT_IS_CONSTRUCTED(&pThis->_vPort)) {
            RegisterPort_Construct(&pThis->_vPort, &registerParameter);
        }
    } else {
        return NULL;
    }

    return &pThis->_vPort.base;
}

PUBLIC void RegisterGroup_DestroyPort(BaseComponent *component, BasePort *port)
{
    (void)component;
    (void)port;
}
