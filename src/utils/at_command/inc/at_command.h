#ifndef __AT_COMMAND_H__
#define __AT_COMMAND_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"
#include "core/common/inc/ring_buffer.h"
#include "core/event/inc/event_handler.h"

#include "port/common/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define AT_COMMAND_MAX_LENGTH                   80
#define AT_COMMAND_MAX_PARAMETERS_NUMBER        10

#define AT_COMMAND_HEADER                       "AT"
#define AT_COMMAND_HEADER_LENGTH                2
#define AT_COMMAND_FOOTER                       "\r"
#define AT_COMMAND_FOOTER_LENGTH                1

#define STATIC_AT_COMMAND(command, handler) {   \
    .base = STATIC_LINKED_LIST_NODE(),          \
    ._command = (command),                      \
    ._handler = (handler)                       \
}

#define LinkedListNode2ATCommand(instance)      \
    BASE2SUB(instance, ATCommand, base)

typedef struct {
    LinkedListNode base;
    const char *_command;
    void (*_handler)(unsigned int argc, const char *argv[]);
} ATCommand;

typedef void (*ATCommandHandler)(unsigned int argc, const char *argv[]);

// Constructor(s) & Destructor(s)
PUBLIC void ConstructATCommand(
    ATCommand *instance,
    const char *command,
    ATCommandHandler handler);

PUBLIC void DestructATCommand(ATCommand *instance);

// Public method(s)
PUBLIC void ResponseATCommand(ATCommand *self, const char *responseString);

PUBLIC STATIC void RegisterATCommand(ATCommand *instance);
PUBLIC STATIC void UnregisterATCommand(ATCommand *instance);
PUBLIC STATIC EventHandler *EventHandlerOfATCommand(void);
PUBLIC STATIC void ProcessATCommand(char *commandString);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __AT_COMMAND_H__
