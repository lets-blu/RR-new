#ifndef __DATA_SELECTOR_H__
#define __DATA_SELECTOR_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DATA_SELECTOR_DATA_BITS 8U

#define LinkedListNode2DataSelector(pThis) \
    CONTAINER_OF(pThis, DataSelector, base)

typedef struct {
    LinkedListNode base;
    unsigned int _startAddress;
    unsigned int _endAddress;
} DataSelector;

// Constructor(s) & Destructor(s)
PUBLIC void DataSelector_Construct(
    DataSelector *pThis,
    unsigned int startAddress,
    unsigned int endAddress);

PUBLIC void DataSelector_Destruct(DataSelector *pThis);

// Public method(s)
PUBLIC unsigned int DataSelector_GetStartAddress(DataSelector *pThis);
PUBLIC unsigned int DataSelector_GetEndAddress(DataSelector *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DATA_SELECTOR_H__
