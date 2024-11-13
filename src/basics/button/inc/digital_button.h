#ifndef __DIGITAL_BUTTON_H__
#define __DIGITAL_BUTTON_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/device/inc/device_manager.h"
#include "core/thread/inc/base_thread.h"

#include "port/common/inc/base_factory.h"
#include "port/common/inc/base_port.h"

#include "basics/button/inc/base_button.h"
#include "basics/button/inc/button_state.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DIGITAL_BUTTON_SCAN_INTERVAL 50

#define BaseThread2DigitalButtonThread(instance) \
    BASE2SUB(instance, DigitalButtonThread, base)

#define BaseButton2DigitalButton(instance) \
    BASE2SUB(instance, DigitalButton, base)

struct DigitalButton;

typedef enum {
    DIGITAL_BUTTON_EVENT_CLICK
} DigitalButtonEvent;

typedef struct {
    DigitalButtonEvent event;
} DigitalButtonEventParameter;

typedef struct {
    BaseThread base;
    struct DigitalButton *_button;
} DigitalButtonThread;

typedef struct DigitalButton {
    BaseButton base;
    const ButtonState *_currentState;

    BasePort *_port;
    unsigned int _pressValue;

    void (*_eventHandler)(
        struct DigitalButton *sender,
        DigitalButtonEventParameter *parameter);

    DigitalButtonThread _thread;
} DigitalButton;

typedef void (*DigitalButtonEventHandler)(
    DigitalButton *,
    DigitalButtonEventParameter *);

// Constructor(s) & Destructor(s)
PUBLIC void ConstructDigitalButton(
    DigitalButton *instance,
    const char *type,
    BasePortParameter *parameter,
    unsigned int pressValue);

PUBLIC void DestructDigitalButton(DigitalButton *instance);

PUBLIC void ConstructDigitalButtonThread(
    DigitalButtonThread *instance,
    DigitalButton *button);

PUBLIC void DestructDigitalButtonThread(DigitalButtonThread *instance);

// Public Method(s)
PUBLIC void SetEventHandlerToDigitalButton(
    DigitalButton *self,
    DigitalButtonEventHandler handler);

PUBLIC void EnableAutoScanToDigitalButton(DigitalButton *self, bool enable);
PUBLIC void ScanDigitalButton(DigitalButton *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DIGITAL_BUTTON_H__
