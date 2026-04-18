#ifndef __SHIFT_REGISTER_H__
#define __SHIFT_REGISTER_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SHIFT_REGISTER_DATA_BITS 8U

#define LinkedListNode2ShiftRegister(pThis) \
    CONTAINER_OF(pThis, ShiftRegister, base)

typedef struct {
    LinkedListNode base;
    uint8_t _data;
} ShiftRegister;

// Constructor(s) & Destructor(s)
PUBLIC void ShiftRegister_Construct(ShiftRegister *pThis);
PUBLIC void ShiftRegister_Destruct(ShiftRegister *pThis);

// Public method(s)
PUBLIC void ShiftRegister_SetBit(ShiftRegister *pThis, unsigned int bit);
PUBLIC void ShiftRegister_ResetBit(ShiftRegister *pThis, unsigned int bit);
PUBLIC uint8_t ShiftRegister_GetData(ShiftRegister *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SHIFT_REGISTER_H__
