#include "digital/selector/inc/data_selector.h"

// Method implement(s)
PUBLIC void DataSelector_Construct(
    DataSelector *pThis,
    unsigned int startAddress,
    unsigned int endAddress)
{
    if (pThis != NULL) {
        LinkedListNode_Construct(&pThis->base);
        pThis->_startAddress = startAddress;
        pThis->_endAddress = endAddress;
    }
}

PUBLIC void DataSelector_Destruct(DataSelector *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(DataSelector));
    }
}

PUBLIC unsigned int DataSelector_GetStartAddress(DataSelector *pThis)
{
    return (pThis == NULL) ? 0 : pThis->_startAddress;
}

PUBLIC unsigned int DataSelector_GetEndAddress(DataSelector *pThis)
{
    return (pThis == NULL) ? 0 : pThis->_endAddress;
}
