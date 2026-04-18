#ifndef __SELECTOR_GROUP_H__
#define __SELECTOR_GROUP_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/device/inc/device_factory.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/component/inc/base_component.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/general_port.h"

#include "digital/selector/inc/data_selector.h"
#include "digital/selector/inc/selector_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SELECTOR_GROUP_DIGITAL_PORT "SelectorPort"

#define BaseComponent2SelectorGroup(pThis) \
    CONTAINER_OF(pThis, SelectorGroup, base)

#define LinkedListNode2SelectorGroup(pThis) \
    BaseComponent2SelectorGroup(LinkedListNode2BaseComponent(pThis))

typedef struct SelectorGroup {
    BaseComponent base;

    BasePort *_addressPort;
    unsigned int _addressPins;
    BasePort *_dataPort;
    unsigned int _dataPin;

    LinkedList _selectors;
    SelectorPort _vPort;
} SelectorGroup;

// Contructor(s) & Destructor(s)
PUBLIC void SelectorGroup_Construct(
    SelectorGroup *pThis,
    void *port,
    unsigned int addressPins,
    unsigned int dataPin);

PUBLIC void SelectorGroup_Destruct(SelectorGroup *pThis);

// Public method(s)
PUBLIC void SelectorGroup_AddSelector(
    SelectorGroup *pThis,
    DataSelector *selector);

PUBLIC void SelectorGroup_RemoveSelector(
    SelectorGroup *pThis,
    DataSelector *selector);

PUBLIC unsigned int SelectorGroup_GetBit(
    SelectorGroup *pThis,
    unsigned int bit);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SELECTOR_GROUP_H__
