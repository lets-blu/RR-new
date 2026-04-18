#include "basics/button/inc/button_state.h"
#include "basics/button/inc/base_button.h"

// Override method(s)
PUBLIC void ButtonStateReleased_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC void ButtonStateReleased_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC const char *ButtonStateReleased_GetName(const ButtonState *pThis);

PUBLIC void ButtonStateConfirmPress_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC void ButtonStateConfirmPress_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC const char *ButtonStateConfirmPress_GetName(const ButtonState *pThis);

PUBLIC void ButtonStatePressed_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC void ButtonStatePressed_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC const char *ButtonStatePressed_GetName(const ButtonState *pThis);

PUBLIC void ButtonStateConfirmRelease_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC void ButtonStateConfirmRelease_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button);

PUBLIC const char *ButtonStateConfirmRelease_GetName(const ButtonState *pThis);

// Virtual methods table(s)
static const ButtonStateVtbl buttonStateReleasedVtbl = {
    .OnPress = ButtonStateReleased_OnPress,
    .OnRelease = ButtonStateReleased_OnRelease,
    .GetName = ButtonStateReleased_GetName,
};

static const ButtonStateVtbl buttonStateConfirmPressVtbl = {
    .OnPress = ButtonStateConfirmPress_OnPress,
    .OnRelease = ButtonStateConfirmPress_OnRelease,
    .GetName = ButtonStateConfirmPress_GetName,
};

static const ButtonStateVtbl buttonStatePressedVtbl = {
    .OnPress = ButtonStatePressed_OnPress,
    .OnRelease = ButtonStatePressed_OnRelease,
    .GetName = ButtonStatePressed_GetName,
};

static const ButtonStateVtbl buttonStateConfirmReleaseVtbl = {
    .OnPress = ButtonStateConfirmRelease_OnPress,
    .OnRelease = ButtonStateConfirmRelease_OnRelease,
    .GetName = ButtonStateConfirmRelease_GetName,
};

// Public method(s)
PUBLIC STATIC const ButtonState buttonStateReleased = {
    .vtbl = &buttonStateReleasedVtbl,
};

PUBLIC STATIC const ButtonState buttonStateConfirmPress = {
    .vtbl = &buttonStateConfirmPressVtbl,
};

PUBLIC STATIC const ButtonState buttonStatePressed = {
    .vtbl = &buttonStatePressedVtbl,
};

PUBLIC STATIC const ButtonState buttonStateConfirmRelease = {
    .vtbl = &buttonStateConfirmReleaseVtbl,
};

// Method implement(s)
PUBLIC void ButtonState_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->OnPress != NULL) {
        pThis->vtbl->OnPress(pThis, button);
    }
}

PUBLIC void ButtonState_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->OnRelease != NULL) {
        pThis->vtbl->OnRelease(pThis, button);
    }
}

PUBLIC const char *ButtonState_GetName(const ButtonState *pThis)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->GetName == NULL) {
        return NULL;
    }

    return pThis->vtbl->GetName(pThis);
}

PUBLIC void ButtonStateReleased_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_CONFIRM_PRESS);
}

PUBLIC void ButtonStateReleased_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    (void)button;
}

PUBLIC const char *ButtonStateReleased_GetName(const ButtonState *pThis)
{
    (void)pThis;
    return "RELEASED";
}

PUBLIC void ButtonStateConfirmPress_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_PRESSED);
}

PUBLIC void ButtonStateConfirmPress_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_RELEASED);
}

PUBLIC const char *ButtonStateConfirmPress_GetName(const ButtonState *pThis)
{
    (void)pThis;
    return "CONFIRM_PRESS";
}

PUBLIC void ButtonStatePressed_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    (void)button;
}

PUBLIC void ButtonStatePressed_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_CONFIRM_RELEASE);
}

PUBLIC const char *ButtonStatePressed_GetName(const ButtonState *pThis)
{
    (void)pThis;
    return "PRESSED";
}

PUBLIC void ButtonStateConfirmRelease_OnPress(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_PRESSED);
}

PUBLIC void ButtonStateConfirmRelease_OnRelease(
    const ButtonState *pThis,
    struct BaseButton *button)
{
    (void)pThis;
    BaseButton_SetState(button, BUTTON_STATE_RELEASED);
    BaseButton_OnClick(button);
}

PUBLIC const char *ButtonStateConfirmRelease_GetName(const ButtonState *pThis)
{
    (void)pThis;
    return "CONFIRM_RELEASE";
}
