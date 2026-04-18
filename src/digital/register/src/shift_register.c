#include "digital/register/inc/shift_register.h"

// Method implement(s)
PUBLIC void ShiftRegister_Construct(ShiftRegister *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Construct(&pThis->base);
        pThis->_data = 0;
    }
}

PUBLIC void ShiftRegister_Destruct(ShiftRegister *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(ShiftRegister));
    }
}

PUBLIC void ShiftRegister_SetBit(ShiftRegister *pThis, unsigned int bit)
{
    if (pThis != NULL && bit < SHIFT_REGISTER_DATA_BITS) {
        pThis->_data |= (1 << bit);
    }
}

PUBLIC void ShiftRegister_ResetBit(ShiftRegister *pThis, unsigned int bit)
{
    if (pThis != NULL && bit < SHIFT_REGISTER_DATA_BITS) {
        pThis->_data &= ~(1 << bit);
    }
}

PUBLIC uint8_t ShiftRegister_GetData(ShiftRegister *pThis)
{
    return (pThis == NULL) ? 0 : pThis->_data;
}
