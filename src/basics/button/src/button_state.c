#include "basics/button/inc/button_state.h"
#include "basics/button/inc/base_button.h"

// Override method(s)
PUBLIC void OnPressInButtonStateReleased(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC void OnReleaseInButtonStateReleased(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC const char *GetNameInButtonStateReleased(const ButtonState *self);

PUBLIC void OnPressInButtonStateConfirmPress(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC void OnReleaseInButtonStateConfirmPress(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC const char *GetNameInButtonStateConfirmPress(const ButtonState *self);

PUBLIC void OnPressInButtonStatePressed(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC void OnReleaseInButtonStatePressed(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC const char *GetNameInButtonStatePressed(const ButtonState *self);

PUBLIC void OnPressInButtonStateConfirmRelease(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC void OnReleaseInButtonStateConfirmRelease(
    const ButtonState *self,
    struct BaseButton *button);

PUBLIC const char *GetNameInButtonStateConfirmRelease(const ButtonState *self);

// Virtual methods table
static const ButtonStateVtbl releasedVtbl = {
    .OnPress = OnPressInButtonStateReleased,
    .OnRelease = OnReleaseInButtonStateReleased,
    .GetName = GetNameInButtonStateReleased
};

static const ButtonStateVtbl confirmPressVtbl = {
    .OnPress = OnPressInButtonStateConfirmPress,
    .OnRelease = OnReleaseInButtonStateConfirmPress,
    .GetName = GetNameInButtonStateConfirmPress
};

static const ButtonStateVtbl pressedVtbl = {
    .OnPress = OnPressInButtonStatePressed,
    .OnRelease = OnReleaseInButtonStatePressed,
    .GetName = GetNameInButtonStatePressed
};

static const ButtonStateVtbl confirmReleaseVtbl = {
    .OnPress = OnPressInButtonStateConfirmRelease,
    .OnRelease = OnReleaseInButtonStateConfirmRelease,
    .GetName = GetNameInButtonStateConfirmRelease
};

// Public member(s)
PUBLIC STATIC const ButtonState buttonStateReleased = {
    .vtbl = &releasedVtbl
};

PUBLIC STATIC const ButtonState buttonStateConfirmPress = {
    .vtbl = &confirmPressVtbl
};

PUBLIC STATIC const ButtonState buttonStatePressed = {
    .vtbl = &pressedVtbl
};

PUBLIC STATIC const ButtonState buttonStateConfirmRelease = {
    .vtbl = &confirmReleaseVtbl
};

// Method implement(s)
PUBLIC void OnPressInButtonStateReleased(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_CONFIRM_PRESS);
}

PUBLIC void OnReleaseInButtonStateReleased(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    (void)button;
}

PUBLIC const char *GetNameInButtonStateReleased(const ButtonState *self)
{
    (void)self;
    return "RELEASED";
}

PUBLIC void OnPressInButtonStateConfirmPress(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_PRESSED);
}

PUBLIC void OnReleaseInButtonStateConfirmPress(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_RELEASED);
}

PUBLIC const char *GetNameInButtonStateConfirmPress(const ButtonState *self)
{
    (void)self;
    return "CONFIRM_PRESS";
}

PUBLIC void OnPressInButtonStatePressed(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    (void)button;
}

PUBLIC void OnReleaseInButtonStatePressed(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_CONFIRM_RELEASE);
}

PUBLIC const char *GetNameInButtonStatePressed(const ButtonState *self)
{
    (void)self;
    return "PRESSED";
}

PUBLIC void OnPressInButtonStateConfirmRelease(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_PRESSED);
}

PUBLIC void OnReleaseInButtonStateConfirmRelease(
    const ButtonState *self,
    struct BaseButton *button)
{
    (void)self;
    SetStateToBaseButton(button, BUTTON_STATE_RELEASED);
    OnClickBaseButton(button);
}

PUBLIC const char *GetNameInButtonStateConfirmRelease(const ButtonState *self)
{
    (void)self;
    return "CONFIRM_RELEASE";
}

PUBLIC void OnPressInButtonState(
    const ButtonState *self,
    struct BaseButton *button)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->OnPress == NULL)
    {
        return;
    }

    self->vtbl->OnPress(self, button);
}

PUBLIC void OnReleaseInButtonState(
    const ButtonState *self,
    struct BaseButton *button)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->OnRelease == NULL)
    {
        return;
    }

    self->vtbl->OnRelease(self, button);
}

PUBLIC const char *GetNameInButtonState(const ButtonState *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->GetName == NULL)
    {
        return NULL;
    }

    return self->vtbl->GetName(self);
}
