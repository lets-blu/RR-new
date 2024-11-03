#ifndef __AT_COMMAND_H__
#define __AT_COMMAND_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"
#include "core/common/inc/ring_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MAX_LENGTH_OF_AT_COMMAND                80
#define MAX_NUMBER_OF_AT_COMMAND_PARAMETERS     10

#define AT_COMMAND_HEADER                       "AT"
#define AT_COMMAND_HEADER_LENGTH                2
#define AT_COMMAND_FOOTER                       "\r"
#define AT_COMMAND_FOOTER_LENGTH                1

#define STATIC_AT_COMMAND(command, callback) {  \
    .base = STATIC_LINKED_LIST_NODE(),          \
    ._command = (command),                      \
    ._callback = (callback)                     \
}

#define LinkedListNode2ATCommand(instance)      \
    BASE2SUB(instance, ATCommand, base)

typedef struct {
    LinkedListNode base;
    const char *_command;
    void (*_callback)(unsigned int argc, const char *argv[]);
} ATCommand;

typedef void (*ATCommandCallback)(unsigned int argc, const char *argv[]);

// Constructor(s) & Destructor(s)
PUBLIC void ConstructATCommand(
    ATCommand *instance,
    const char *command,
    ATCommandCallback callback);

PUBLIC void DestructATCommand(ATCommand *instance);

// Public method(s)
PUBLIC void ResponseATCommand(ATCommand *self, const char *responseString);
PUBLIC STATIC void RegisterATCommand(ATCommand *instance);
PUBLIC STATIC void UnregisterATCommand(ATCommand *instance);

PUBLIC STATIC void RingBufferCallbackOfATCommand(
    RingBufferEvent event,
    RingBufferEventParameter *parameter);

PUBLIC STATIC void ProcessATCommand(char *commandString);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __AT_COMMAND_H__
