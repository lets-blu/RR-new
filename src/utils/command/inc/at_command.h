#ifndef __AT_COMMAND_H__
#define __AT_COMMAND_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/core/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define AT_COMMAND_MAX_LENGTH 80U
#define AT_COMMAND_MAX_PARAMETER_NUMBER 10

#define AT_COMMAND_HEADER "AT"
#define AT_COMMAND_HEADER_LENGTH 2U
#define AT_COMMAND_FOOTER "\r"
#define AT_COMMAND_FOOTER_LENGTH 1U

#define AT_COMMAND_COMMAND_SEPARATOR "="
#define AT_COMMAND_COMMAND_SEPARATOR_LENGTH 1U
#define AT_COMMAND_RESPONSE_SEPARATOR ":"
#define AT_COMMAND_RESPONSE_SEPARATOR_LENGTH 1U
#define AT_COMMAND_ARGUMENT_SEPARATOR ","
#define AT_COMMAND_ARGUMENT_SEPARATOR_LENGTH 1U

#define AT_COMMAND_OK_RESPONSE "OK" AT_COMMAND_FOOTER
#define AT_COMMAND_OK_RESPONSE_LENGTH 2U + AT_COMMAND_FOOTER_LENGTH
#define AT_COMMAND_ERROR_RESPONSE "ERROR" AT_COMMAND_FOOTER
#define AT_COMMAND_ERROR_RESPONSE_LENGTH 5U + AT_COMMAND_FOOTER_LENGTH

#define AT_COMMAND_EVENT_ARGS_BASE {  \
    ._reserved = EVENT_ARGS_RESERVED, \
}

#define LinkedListNode2ATCommand(pThis) \
    CONTAINER_OF(pThis, ATCommand, base)

#define EventArgs2ATCommandEventArgs(pThis) \
    CONTAINER_OF(pThis, ATCommandEventArgs, base)

typedef struct {
    LinkedListNode base;
    const char *_command;
    EventHandler _handler;
} ATCommand;

typedef struct {
    EventArgs base;
    int argc;
    char *argv[AT_COMMAND_MAX_PARAMETER_NUMBER];
} ATCommandEventArgs;

// Constructor(s) & Destructor(s)
PUBLIC void ATCommand_Construct(
    ATCommand *pThis,
    const char *command,
    EventHandler handler);

PUBLIC void ATCommand_Destruct(ATCommand *pThis);

// Public method(s)
PUBLIC bool ATCommand_Response(ATCommand *pThis, const char *response);
PUBLIC STATIC void ATCommand_SetSerial(BaseSerial *newSerial);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __AT_COMMAND_H__
