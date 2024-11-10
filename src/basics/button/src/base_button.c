#include "basics/button/inc/base_button.h"

// Private member(s)
PRIVATE STATIC Logger logger = STATIC_LOGGER("BaseButton", LOGGER_LEVEL_INFO);

// Method implement(s)
PROTECTED void ConstructBaseButton(BaseButton *instance)
{
    if (instance != NULL)
    {
        RegisterLogger(&logger);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseButton(BaseButton *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(BaseButton));
    }
}

PUBLIC void SetStateToBaseButton(BaseButton *self, const ButtonState *state)
{
    const ButtonState *currentState = GetStateFromBaseButton(self);

    if (self == NULL || self->vtbl == NULL || self->vtbl->SetState == NULL)
    {
        return;
    }

    LOGGER_I(&logger, "Set state to %p, %s -> %s",
        (void *)self,
        GetNameInButtonState(currentState),
        GetNameInButtonState(state));

    self->vtbl->SetState(self, state);
}

PUBLIC const ButtonState *GetStateFromBaseButton(BaseButton *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->GetState == NULL)
    {
        return NULL;
    }

    return self->vtbl->GetState(self);
}

PUBLIC void OnClickBaseButton(BaseButton *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->OnClick == NULL)
    {
        return;
    }

    self->vtbl->OnClick(self);
}
