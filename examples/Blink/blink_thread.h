#ifndef __BLINK_THREAD_H__
#define __BLINK_THREAD_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include <RR.h>
#include <core/common/inc/keywords.h>
#include <core/thread/inc/base_thread.h>

#define BaseThread2BlinkThread(instance) \
    BASE2SUB(instance, BlinkThread, base)

typedef struct {
    BaseThread base;
    LED *_led;
    unsigned long _delay;
} BlinkThread;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructBlinkThread(
    BlinkThread *instance,
    LED *led,
    unsigned long delay);

PUBLIC void DestructBlinkThread(BlinkThread *instance);

// Public method(s)
PUBLIC STATIC void RunBlinkThreadTask(void *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BLINK_THREAD_H__
