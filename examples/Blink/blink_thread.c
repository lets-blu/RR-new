#include "blink_thread.h"

// Override method(s)
PUBLIC BaseThreadState RunBlinkThreadBase(BaseThread *thread);

// Virtual methods table
static const BaseThreadVtbl baseVtbl = {
    .Run = RunBlinkThreadBase
};

// Method implement(s)
PUBLIC void ConstructBlinkThread(
    BlinkThread *instance,
    LED *led,
    unsigned long delay)
{
    if (instance == NULL)
    {
        return;
    }

    ConstructBaseThread(&instance->base);
    instance->base.vtbl = &baseVtbl;

    instance->_led = led;
    instance->_delay = delay;
}

PUBLIC void DestructBlinkThread(BlinkThread *instance)
{
    if (instance != NULL)
    {
        DestructBaseThread(&instance->base);
        memset(instance, 0, sizeof(BlinkThread));
    }
}

PUBLIC BaseThreadState RunBlinkThreadBase(BaseThread *thread)
{
    BlinkThread *self = BaseThread2BlinkThread(thread);

    if (thread == NULL)
    {
        return BASE_THREAD_STATE_ENDED;
    }

    BASE_THREAD_BEGIN(thread);

    for (;;)
    {
        TurnOnLED(self->_led);
        BASE_THREAD_DELAY(thread, self->_delay);

        TurnOffLED(self->_led);
        BASE_THREAD_DELAY(thread, self->_delay);
    }

    BASE_THREAD_END(thread);
}

PUBLIC STATIC void RunBlinkThreadTask(void *parameter)
{
    BlinkThread *self = (BlinkThread *)parameter;

    for (;;)
    {
        RunBaseThread(&self->base);
    }
}
