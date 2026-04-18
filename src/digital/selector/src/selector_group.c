#include "digital/selector/inc/selector_group.h"

// Override method(s)
PUBLIC BasePort *SelectorGroup_CreatePort(
    BaseComponent *component,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void SelectorGroup_DestroyPort(BaseComponent *component, BasePort *port);

// Virtual methods table(s)
static const BaseComponentVtbl baseVtbl = {
    .CreatePort = SelectorGroup_CreatePort,
    .DestroyPort = SelectorGroup_DestroyPort,
};

// Method implement(s)
PUBLIC void SelectorGroup_Construct(
    SelectorGroup *pThis,
    void *port,
    unsigned int addressPins,
    unsigned int dataPin)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = port,
    };

    DeviceFactory *factory = DeviceFactory_GetInstance();

    if (pThis == NULL) {
        return;
    }

    BaseComponent_Construct(&pThis->base);
    pThis->base.vtbl = &baseVtbl;

    pThis->_addressPort = DeviceFactory_CreatePort(
        factory,
        GENERAL_ADDRESS_PORT,
        &parameter.base);

    pThis->_addressPins = addressPins;
    BasePort_SetMode(pThis->_addressPort, addressPins, BASE_PORT_MODE_OUTPUT);

    pThis->_dataPort = DeviceFactory_CreatePort(
        factory,
        GENERAL_DIGITAL_PORT,
        &parameter.base);

    pThis->_dataPin = dataPin;
    BasePort_SetMode(pThis->_dataPort, dataPin, BASE_PORT_MODE_INPUT);
    LinkedList_Construct(&pThis->_selectors);
}

PUBLIC void SelectorGroup_Destruct(SelectorGroup *pThis)
{
    DeviceFactory *factory = DeviceFactory_GetInstance();

    if (pThis == NULL) {
        return;
    }

    BaseComponent_Destruct(&pThis->base);
    DeviceFactory_DestroyPort(factory, pThis->_addressPort);
    DeviceFactory_DestroyPort(factory, pThis->_dataPort);
    LinkedList_Destruct(&pThis->_selectors);

    memset(pThis, 0, sizeof(SelectorGroup));
}

PUBLIC void SelectorGroup_AddSelector(
    SelectorGroup *pThis,
    DataSelector *selector)
{
    if (pThis != NULL && selector != NULL) {
        LinkedList_AddTail(&pThis->_selectors, &selector->base);
    }
}

PUBLIC void SelectorGroup_RemoveSelector(
    SelectorGroup *pThis,
    DataSelector *selector)
{
    if (pThis != NULL && selector != NULL) {
        LinkedList_RemoveNode(&pThis->_selectors, &selector->base);
    }
}

PUBLIC unsigned int SelectorGroup_GetBit(
    SelectorGroup *pThis,
    unsigned int bit)
{
    unsigned int value = 0;
    bool hasAddress = false;
    LinkedListIterator iterator;

    if (pThis == NULL) {
        return 0;
    }

    LinkedListIterator_Construct(&iterator, &pThis->_selectors);

    while (LinkedListIterator_HasNext(&iterator)) {
        DataSelector *selector = LinkedListNode2DataSelector(
            LinkedListIterator_GetNext(&iterator));

        if (bit >= DataSelector_GetStartAddress(selector)
            && bit <= DataSelector_GetEndAddress(selector)) {
            hasAddress = true;
            break;
        }
    }

    LinkedListIterator_Destruct(&iterator);

    if (hasAddress) {
        BasePort_Write(pThis->_addressPort, pThis->_addressPins, bit);
        value = BasePort_Read(pThis->_dataPort, pThis->_dataPin);
    }

    return value;
}

PUBLIC BasePort *SelectorGroup_CreatePort(
    BaseComponent *component,
    const char *type,
    BasePortParameter *parameter)
{
    SelectorGroup *pThis = BaseComponent2SelectorGroup(component);

    if (component == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, SELECTOR_GROUP_DIGITAL_PORT) == 0) {
        SelectorPortParameter *selectorParameter
            = BasePortParameter2SelectorPortParameter(parameter);

        if (selectorParameter->group != pThis) {
            return NULL;
        }

        if (!SELECTOR_PORT_IS_CONSTRUCTED(&pThis->_vPort)) {
            SelectorPort_Construct(&pThis->_vPort, selectorParameter);
        }
    } else if (strcmp(type, GENERAL_DIGITAL_PORT) == 0) {
        GeneralPortParameter *generalParameter
            = BasePortParameter2GeneralPortParameter(parameter);

        SelectorPortParameter selectorParameter = {
            .base = SELECTOR_PORT_PARAMETER_BASE,
            .group = pThis,
        };

        if (generalParameter->port != pThis) {
            return NULL;
        }

        if (!SELECTOR_PORT_IS_CONSTRUCTED(&pThis->_vPort)) {
            SelectorPort_Construct(&pThis->_vPort, &selectorParameter);
        }
    } else {
        return NULL;
    }

    return &pThis->_vPort.base;
}

PUBLIC void SelectorGroup_DestroyPort(BaseComponent *component, BasePort *port)
{
    (void)component;
    (void)port;
}
