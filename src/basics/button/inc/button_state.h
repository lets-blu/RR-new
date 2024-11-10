#ifndef __BUTTON_STATE_H__
#define __BUTTON_STATE_H__

#include <stddef.h>
#include "core/common/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BUTTON_STATE_RELEASED           &buttonStateReleased
#define BUTTON_STATE_CONFIRM_PRESS      &buttonStateConfirmPress
#define BUTTON_STATE_PRESSED            &buttonStatePressed
#define BUTTON_STATE_CONFIRM_RELEASE    &buttonStateConfirmRelease

struct BaseButton;
struct ButtonStateVtbl;

typedef struct {
    const struct ButtonStateVtbl *vtbl;
} ButtonState;

typedef struct ButtonStateVtbl {
    void (*OnPress)(
        const ButtonState *self,
        struct BaseButton *button);

    void (*OnRelease)(
        const ButtonState *self,
        struct BaseButton *button);

    const char *(*GetName)(const ButtonState *self);
} ButtonStateVtbl;

// Public member(s)
extern PUBLIC STATIC const ButtonState buttonStateReleased;
extern PUBLIC STATIC const ButtonState buttonStateConfirmPress;
extern PUBLIC STATIC const ButtonState buttonStatePressed;
extern PUBLIC STATIC const ButtonState buttonStateConfirmRelease;

// Public method(s)
PUBLIC void OnPressInButtonState(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC void OnReleaseInButtonState(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC const char *GetNameInButtonState(const ButtonState *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BUTTON_STATE_H__
