#ifndef __REGISTER_GROUP_H__
#define __REGISTER_GROUP_H__

#include <stddef.h>
#include <string.h>

#include "core/device/inc/device_factory.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/component/inc/base_component.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/general_port.h"

#include "digital/register/inc/register_port.h"
#include "digital/register/inc/shift_register.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define REGISTER_GROUP_DIGITAL_PORT "RegisterPort"

#define BaseComponent2RegisterGroup(pThis) \
    CONTAINER_OF(pThis, RegisterGroup, base)

#define LinkedListNode2RegisterGroup(pThis) \
    BaseComponent2RegisterGroup(LinkedListNode2BaseComponent(pThis))

typedef struct RegisterGroup {
    BaseComponent base;

    LinkedList _registers;
    unsigned int _registersNumber;

    BasePort *_port;
    unsigned int _serPin;
    unsigned int _sckPin;
    unsigned int _rckPin;

    RegisterPort _vPort;
} RegisterGroup;

typedef struct {
    void *port;
    unsigned int serPin;
    unsigned int sckPin;
    unsigned int rckPin;
} RegisterGroupParameter;

// Constructor(s) & Destructor(s)
PUBLIC void RegisterGroup_Construct(
    RegisterGroup *pThis,
    RegisterGroupParameter *parameter);

PUBLIC void RegisterGroup_Destruct(RegisterGroup *pThis);

// Public method(s)
PUBLIC void RegisterGroup_AddRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister);

PUBLIC void RegisterGroup_RemoveRegister(
    RegisterGroup *pThis,
    ShiftRegister *pRegister);

PUBLIC void RegisterGroup_SetBit(RegisterGroup *pThis, unsigned int bit);
PUBLIC void RegisterGroup_ResetBit(RegisterGroup *pThis, unsigned int bit);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __REGISTER_GROUP_H__
