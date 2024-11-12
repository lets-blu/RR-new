#include "basics/button/inc/digital_button.h"

// Override method(s)
PUBLIC void SetStateToDigitalButtonBase(
    BaseButton *button,
    const ButtonState *state);

PUBLIC const ButtonState *GetStateFromDigitalButtonBase(BaseButton *button);
PUBLIC void OnClickDigitalButtonBase(BaseButton *button);
PUBLIC BaseThreadState RunDigitalButtonThreadBase(BaseThread *thread);

// Virtual methods table
static const BaseButtonVtbl buttonVtbl = {
    .SetState = SetStateToDigitalButtonBase,
    .GetState = GetStateFromDigitalButtonBase,
    .OnClick = OnClickDigitalButtonBase
};

static const BaseThreadVtbl threadVtbl = {
    .Run = RunDigitalButtonThreadBase
};

// Method implement(s)
PUBLIC void ConstructDigitalButton(
    DigitalButton *instance,
    const char *type,
    BasePortParameter *parameter,
    unsigned int pressValue)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    ConstructBaseButton(&instance->base);
    instance->base.vtbl = &buttonVtbl;
    instance->_currentState = BUTTON_STATE_RELEASED;

    instance->_port = CreatePortWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        type,
        parameter);

    instance->_pressValue = pressValue;
    instance->_clickCallback = NULL;
    SetupBasePort(instance->_port, BASE_PORT_MODE_INPUT);

    ConstructDigitalButtonThread(&instance->_thread, instance);
}

PUBLIC void DestructDigitalButton(DigitalButton *instance)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (instance == NULL)
    {
        return;
    }

    DestructDigitalButtonThread(&instance->_thread);

    DestroyPortWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        NULL,
        instance->_port);

    DestructBaseButton(&instance->base);
    memset(instance, 0, sizeof(DigitalButton));
}

PUBLIC void ConstructDigitalButtonThread(
    DigitalButtonThread *instance,
    DigitalButton *button)
{
    if (instance != NULL)
    {
        ConstructBaseThread(&instance->base);
        instance->base.vtbl = &threadVtbl;
        instance->_button = button;
    }
}

PUBLIC void DestructDigitalButtonThread(DigitalButtonThread *instance)
{
    if (instance != NULL)
    {
        DestructBaseThread(&instance->base);
        memset(instance, 0, sizeof(DigitalButtonThread));
    }
}

PUBLIC void SetClickCallbackToDigitalButton(
    DigitalButton *self,
    DigitalButtonClickCallback callback)
{
    if (self != NULL)
    {
        self->_clickCallback = callback;
    }
}

PUBLIC void EnableAutoScanToDigitalButton(DigitalButton *self, bool enable)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (self == NULL)
    {
        return;
    }

    if (enable)
    {
        AddThreadToDeviceManager(
            manager,
            DEVICE_MANAGER_THREAD_DRIVER_INPUT,
            &self->_thread.base);
    }
    else
    {
        RemoveThreadFromDeviceManager(
            manager,
            DEVICE_MANAGER_THREAD_DRIVER_INPUT,
            &self->_thread.base);
    }
}

PUBLIC void ScanDigitalButton(DigitalButton *self)
{
    unsigned int value = BASE_PORT_VALUE_LOW;

    if (self == NULL)
    {
        return;
    }

    value = ReadBasePort(self->_port);

    if (value == self->_pressValue)
    {
        OnPressInButtonState(self->_currentState, &self->base);
    }
    else
    {
        OnReleaseInButtonState(self->_currentState, &self->base);
    }
}

PUBLIC void SetStateToDigitalButtonBase(
    BaseButton *button,
    const ButtonState *state)
{
    DigitalButton *self = BaseButton2DigitalButton(button);

    if (button != NULL && state != NULL)
    {
        self->_currentState = state;
    }
}

PUBLIC const ButtonState *GetStateFromDigitalButtonBase(BaseButton *button)
{
    DigitalButton *self = BaseButton2DigitalButton(button);
    return (button == NULL) ? NULL : self->_currentState;
}

PUBLIC void OnClickDigitalButtonBase(BaseButton *button)
{
    DigitalButton *self = BaseButton2DigitalButton(button);

    if (button != NULL && self->_clickCallback != NULL)
    {
        self->_clickCallback(self);
    }
}

PUBLIC BaseThreadState RunDigitalButtonThreadBase(BaseThread *thread)
{
    DigitalButtonThread *self = BaseThread2DigitalButtonThread(thread);

    if (thread == NULL)
    {
        return BASE_THREAD_STATE_ENDED;
    }

    BEGIN_BASE_THREAD(thread);

    for (;;)
    {
        ScanDigitalButton(self->_button);
        DELAY_BASE_THREAD(thread, DIGITAL_BUTTON_SCAN_INTERVAL);
    }

    END_BASE_THREAD(thread);
}
