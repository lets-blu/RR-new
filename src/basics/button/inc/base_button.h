#ifndef __BASE_BUTTON__
#define __BASE_BUTTON__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/logger/inc/logger.h"
#include "basics/button/inc/button_state.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct BaseButtonVtbl;

typedef struct BaseButton {
    const struct BaseButtonVtbl *vtbl;
} BaseButton;

typedef struct BaseButtonVtbl {
    void (*SetState)(BaseButton *self, const ButtonState *state);
    const ButtonState *(*GetState)(BaseButton *self);
    void (*OnClick)(BaseButton *self);
} BaseButtonVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseButton(BaseButton *instance);
PROTECTED void DestructBaseButton(BaseButton *instance);

// Public method(s)
PUBLIC void SetStateToBaseButton(BaseButton *self, const ButtonState *state);
PUBLIC const ButtonState *GetStateFromBaseButton(BaseButton *self);
PUBLIC void OnClickBaseButton(BaseButton *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_BUTTON__
