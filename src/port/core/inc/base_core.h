#ifndef __BASE_CORE_H__
#define __BASE_CORE_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct BaseCoreVtbl;

typedef struct {
    const struct BaseCoreVtbl *vtbl;
} BaseCore;

typedef struct BaseCoreVtbl {
    BasePort *(*CreatePort)(
        BaseCore *,
        const char *,
        BasePortParameter *);

    void (*DestroyPort)(BaseCore *, BasePort *);

    BaseSerial *(*CreateSerial)(
        BaseCore *,
        const char *,
        BaseSerialParameter *);

    void (*DestroySerial)(BaseCore *, BaseSerial *);
    unsigned long (*GetTime)(BaseCore *);
    void (*Run)(BaseCore *);
} BaseCoreVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseCore_Construct(BaseCore *pThis);
PROTECTED void BaseCore_Destruct(BaseCore *pThis);

// Public method(s)
PUBLIC BasePort *BaseCore_CreatePort(
    BaseCore *pThis,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void BaseCore_DestroyPort(BaseCore *pThis, BasePort *port);

PUBLIC BaseSerial *BaseCore_CreateSerial(
    BaseCore *pThis,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void BaseCore_DestroySerial(BaseCore *pThis, BaseSerial *serial);

PUBLIC unsigned long BaseCore_GetTime(BaseCore *pThis);
PUBLIC void BaseCore_Run(BaseCore *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_CORE_H__
