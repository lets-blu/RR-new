#ifndef __BASE_BUTTON_H__
#define __BASE_BUTTON_H__

#include <stddef.h>
#include <string.h>

#include "basics/button/inc/button_state.h"
#include "core/utils/inc/keywords.h"
#include "utils/logger/inc/logger.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct BaseButtonVtbl;

typedef struct BaseButton {
    const struct BaseButtonVtbl *vtbl;
} BaseButton;

typedef struct BaseButtonVtbl {
    void (*SetState)(BaseButton *, const ButtonState *);
    const ButtonState *(*GetState)(BaseButton *);
    void (*OnClick)(BaseButton *);
} BaseButtonVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseButton_Construct(BaseButton *pThis);
PROTECTED void BaseButton_Destruct(BaseButton *pThis);

// Public method(s)
PUBLIC void BaseButton_SetState(BaseButton *pThis, const ButtonState *state);
PUBLIC const ButtonState *BaseButton_GetState(BaseButton *pThis);
PUBLIC void BaseButton_OnClick(BaseButton *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_BUTTON_H__
