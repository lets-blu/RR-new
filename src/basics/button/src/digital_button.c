#include "basics/button/inc/digital_button.h"

// Private method(s)
PRIVATE void DigitalButtonCoroutine_Construct(
    DigitalButtonCoroutine *pThis,
    DigitalButton *button);

PRIVATE void DigitalButtonCoroutine_Destruct(DigitalButtonCoroutine *pThis);

// Override method(s)
PUBLIC CoroutineState DigitalButtonCoroutine_Run(LinkedCoroutine *coroutine);

PUBLIC void DigitalButton_SetState(
    BaseButton *button,
    const ButtonState *state);

PUBLIC const ButtonState *DigitalButton_GetState(BaseButton *button);
PUBLIC void DigitalButton_OnClick(BaseButton *button);

// Virtual methods table(s)
static const LinkedCoroutineVtbl coroutineVtbl = {
    .Run = DigitalButtonCoroutine_Run,
};

static const BaseButtonVtbl buttonVtbl = {
    .SetState = DigitalButton_SetState,
    .GetState = DigitalButton_GetState,
    .OnClick = DigitalButton_OnClick,
};

// Method implement(s)
PUBLIC void DigitalButton_Construct(
    DigitalButton *pThis,
    void *port,
    unsigned int pin,
    unsigned int pressValue)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = port,
    };

    if (pThis == NULL) {
        return;
    }

    BaseButton_Construct(&pThis->base);
    pThis->base.vtbl = &buttonVtbl;
    pThis->_state = BUTTON_STATE_RELEASED;

    pThis->_port = DeviceFactory_CreatePort(
        DeviceFactory_GetInstance(),
        GENERAL_DIGITAL_PORT,
        &parameter.base);

    pThis->_pin = pin;
    pThis->_pressValue = pressValue;
    BasePort_SetMode(pThis->_port, pin, BASE_PORT_MODE_INPUT);

    pThis->_handler = NULL;
    DigitalButtonCoroutine_Construct(&pThis->_coroutine, pThis);
}

PUBLIC void DigitalButton_Destruct(DigitalButton *pThis)
{
    if (pThis == NULL) {
        return;
    }

    DigitalButtonCoroutine_Destruct(&pThis->_coroutine);
    DeviceFactory_DestroyPort(DeviceFactory_GetInstance(), pThis->_port);
    BaseButton_Destruct(&pThis->base);

    memset(pThis, 0, sizeof(DigitalButton));
}

PRIVATE void DigitalButtonCoroutine_Construct(
    DigitalButtonCoroutine *pThis,
    DigitalButton *button)
{
    LinkedCoroutine_Construct(&pThis->base);
    pThis->base.vtbl = &coroutineVtbl;
    pThis->_button = button;
}

PRIVATE void DigitalButtonCoroutine_Destruct(DigitalButtonCoroutine *pThis)
{
    LinkedCoroutine_Destruct(&pThis->base);
    memset(pThis, 0, sizeof(DigitalButtonCoroutine));
}

PUBLIC void DigitalButton_SetEventHandler(
    DigitalButton *pThis,
    EventHandler handler)
{
    if (pThis != NULL) {
        pThis->_handler = handler;
    }
}

PUBLIC void DigitalButton_EnableSample(DigitalButton *pThis, bool enable)
{
    DeviceManager *manager = DeviceManager_GetInstance();

    if (pThis == NULL) {
        return;
    }

    if (enable) {
        DeviceManager_AddCoroutine(manager, &pThis->_coroutine.base);
    } else {
        DeviceManager_RemoveCoroutine(manager, &pThis->_coroutine.base);
    }
}

PUBLIC CoroutineState DigitalButtonCoroutine_Run(LinkedCoroutine *coroutine)
{
    DigitalButton *button = NULL;

    DigitalButtonCoroutine *pThis
        = LinkedCoroutine2DigitalButtonCoroutine(coroutine);

    if (coroutine == NULL) {
        return COROUTINE_STATE_ENDED;
    }

    button = pThis->_button;
    LINKED_COROUTINE_BEGIN(coroutine);

    for (;;) {
        unsigned int value = BasePort_Read(button->_port, button->_pin);

        if (value == button->_pressValue) {
            ButtonState_OnPress(button->_state, &button->base);
        } else {
            ButtonState_OnRelease(button->_state, &button->base);
        }

        LINKED_COROUTINE_SLEEP(coroutine, DIGITAL_BUTTON_SAMPLE_INTERVAL);
    }

    LINKED_COROUTINE_END(coroutine);
}

PUBLIC void DigitalButton_SetState(
    BaseButton *button,
    const ButtonState *state)
{
    DigitalButton *pThis = BaseButton2DigitalButton(button);

    if (button != NULL) {
        pThis->_state = state;
    }
}

PUBLIC const ButtonState *DigitalButton_GetState(BaseButton *button)
{
    return (button == NULL) ? NULL : BaseButton2DigitalButton(button)->_state;
}

PUBLIC void DigitalButton_OnClick(BaseButton *button)
{
    DigitalButton *pThis = BaseButton2DigitalButton(button);

    if (button == NULL) {
        return;
    }

    if (pThis->_handler != NULL) {
        pThis->_handler(pThis, NULL);
    }
}
