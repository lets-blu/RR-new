#include "basics/button/inc/base_button.h"

// Private member(s)
PRIVATE STATIC Logger logger = LOGGER_STATIC("BaseButton", LOGGER_LEVEL_INFO);

// Method implement(s)
PROTECTED void BaseButton_Construct(BaseButton *pThis)
{
    if (pThis != NULL) {
        Logger_Register(&logger);
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseButton_Destruct(BaseButton *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseButton));
    }
}

PUBLIC void BaseButton_SetState(BaseButton *pThis, const ButtonState *state)
{
    const ButtonState *current = BaseButton_GetState(pThis);

    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->SetState == NULL) {
        return;
    }

    LOGGER_I(&logger, "Set state %p, %s -> %s",
        pThis, ButtonState_GetName(current), ButtonState_GetName(state));

    pThis->vtbl->SetState(pThis, state);
}

PUBLIC const ButtonState *BaseButton_GetState(BaseButton *pThis)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->GetState == NULL) {
        return NULL;
    }

    return pThis->vtbl->GetState(pThis);
}

PUBLIC void BaseButton_OnClick(BaseButton *pThis)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->OnClick != NULL) {
        pThis->vtbl->OnClick(pThis);
    }
}
