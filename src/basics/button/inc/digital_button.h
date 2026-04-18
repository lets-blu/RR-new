#ifndef __DIGITAL_BUTTON_H__
#define __DIGITAL_BUTTON_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/coroutine/inc/linked_coroutine.h"
#include "core/device/inc/device_factory.h"
#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"

#include "port/core/inc/base_port.h"
#include "port/core/inc/general_port.h"

#include "basics/button/inc/base_button.h"
#include "basics/button/inc/button_state.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DIGITAL_BUTTON_SAMPLE_INTERVAL 50U

#define LinkedCoroutine2DigitalButtonCoroutine(pThis) \
    CONTAINER_OF(pThis, DigitalButtonCoroutine, base)

#define LinkedListNode2DigitalButtonCoroutine(pThis) \
    LinkedCoroutine2DigitalButtonCoroutine(          \
        LinkedListNode2LinkedCoroutine(pThis))

#define BaseButton2DigitalButton(pThis) \
    CONTAINER_OF(pThis, DigitalButton, base)

struct DigitalButton;

typedef struct {
    LinkedCoroutine base;
    struct DigitalButton *_button;
} DigitalButtonCoroutine;

typedef struct DigitalButton {
    BaseButton base;
    const ButtonState *_state;

    BasePort *_port;
    unsigned int _pin;
    unsigned int _pressValue;

    EventHandler _handler;
    DigitalButtonCoroutine _coroutine;
} DigitalButton;

// Constructor(s) & Destructor(s)
PUBLIC void DigitalButton_Construct(
    DigitalButton *pThis,
    void *port,
    unsigned int pin,
    unsigned int pressValue);

PUBLIC void DigitalButton_Destruct(DigitalButton *pThis);

// Public method(s)
PUBLIC void DigitalButton_SetEventHandler(
    DigitalButton *pThis,
    EventHandler handler);

PUBLIC void DigitalButton_EnableSample(DigitalButton *pThis, bool enable);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DIGITAL_BUTTON_H__
