#include "utils/command/inc/at_command.h"

// Private member(s)
PRIVATE STATIC BaseSerial *serial = NULL;
PRIVATE STATIC LinkedList commands = LINKED_LIST_STATIC();

// Private method(s)
PRIVATE STATIC void ATCommand_EventHandler(void *sender, EventArgs *args);
PRIVATE STATIC void ATCommand_Process(char *command);

PRIVATE STATIC bool ATCommand_FindCallback(
    LinkedListNode *node,
    const void *data);

PRIVATE STATIC bool ATCommand_SendResponse(const char *response, size_t length);

// Method implement(s)
PUBLIC void ATCommand_Construct(
    ATCommand *pThis,
    const char *command,
    EventHandler handler)
{
    if (pThis == NULL || command == NULL || handler == NULL) {
        return;
    }

    LinkedListNode_Construct(&pThis->base);
    pThis->_command = command;
    pThis->_handler = handler;

    LinkedList_AddTail(&commands, &pThis->base);
}

PUBLIC void ATCommand_Destruct(ATCommand *pThis)
{
    if (pThis != NULL) {
        LinkedList_RemoveNode(&commands, &pThis->base);
        LinkedListNode_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(ATCommand));
    }
}

PUBLIC bool ATCommand_Response(ATCommand *pThis, const char *response)
{
    size_t length = 0;
    char buffer[AT_COMMAND_MAX_LENGTH] = {0};

    if (pThis == NULL || response == NULL) {
        return false;
    }

    strcpy(buffer, pThis->_command);
    length += strlen(pThis->_command);

    strcpy(buffer + length, AT_COMMAND_RESPONSE_SEPARATOR);
    length += AT_COMMAND_RESPONSE_SEPARATOR_LENGTH;

    strcpy(buffer + length, response);
    length += strlen(response);

    strcpy(buffer + length, AT_COMMAND_FOOTER);
    length += AT_COMMAND_FOOTER_LENGTH;

    return ATCommand_SendResponse(buffer, length);
}

PUBLIC STATIC void ATCommand_SetSerial(BaseSerial *newSerial)
{
    if (newSerial == NULL) {
        BaseSerial_SetEventHandler(serial, NULL);
    } else {
        BaseSerial_SetEventHandler(newSerial, ATCommand_EventHandler);
    }

    serial = newSerial;
}

PRIVATE STATIC void ATCommand_EventHandler(void *sender, EventArgs *args)
{
    (void)sender;

    RingBufferPacketParameter packetParameter = {
        .header = (const uint8_t *)AT_COMMAND_HEADER,
        .headerLength = AT_COMMAND_HEADER_LENGTH,
        .footer = (const uint8_t *)AT_COMMAND_FOOTER,
        .footerLength = AT_COMMAND_FOOTER_LENGTH,
    };

    RingBufferPacketResult packetResult = {0};
    uint8_t commandBuffer[AT_COMMAND_MAX_LENGTH] = {0};
    BaseSerialEventArgs *serialArgs = EventArgs2BaseSerialEventArgs(args);

    if (args == NULL
        || serialArgs->event != BASE_SERIAL_EVENT_DATA_RECEIVED
        || serialArgs->buffer == NULL) {
        return;
    }

    packetResult = RingBuffer_FindPacket(
        serialArgs->buffer,
        &packetParameter);

    if (packetResult.invalidLength != 0) {
        RingBuffer_Read(
            serialArgs->buffer,
            commandBuffer,
            AT_COMMAND_MAX_LENGTH);
    }

    if (packetResult.packetLength != 0) {
        RingBuffer_Read(
            serialArgs->buffer,
            commandBuffer,
            AT_COMMAND_MAX_LENGTH);

        ATCommand_Process((char *)commandBuffer);
    }
}

PRIVATE STATIC void ATCommand_Process(char *command)
{
    ATCommand *atCommand = NULL;
    char *end = NULL;
    char *parameter = NULL;

    ATCommandEventArgs args = {
        .base = AT_COMMAND_EVENT_ARGS_BASE,
    };

    LinkedListNode *node = LinkedList_FindNode(
        &commands,
        ATCommand_FindCallback,
        command + AT_COMMAND_HEADER_LENGTH);

    // 1. Find command
    if (node == NULL) {
        ATCommand_SendResponse(
            AT_COMMAND_ERROR_RESPONSE,
            AT_COMMAND_ERROR_RESPONSE_LENGTH);

        return;
    }

    atCommand = LinkedListNode2ATCommand(node);

    // 2. Remove footer
    end = strstr(command, AT_COMMAND_FOOTER);

    if (end != NULL) {
        *end = '\0';
    }

    // 3. If there is no parameter
    parameter = strstr(command, AT_COMMAND_COMMAND_SEPARATOR);

    if (parameter == NULL) {
        atCommand->_handler(atCommand, &args.base);

        ATCommand_SendResponse(
            AT_COMMAND_OK_RESPONSE,
            AT_COMMAND_OK_RESPONSE_LENGTH);

        return;
    }

    // 4. If there is parameter
    *parameter = '\0';

    parameter = strtok(
        parameter + AT_COMMAND_COMMAND_SEPARATOR_LENGTH,
        AT_COMMAND_ARGUMENT_SEPARATOR);

    while (parameter != NULL && args.argc < AT_COMMAND_MAX_PARAMETER_NUMBER) {
        args.argv[args.argc++] = parameter;
        parameter = strtok(NULL, AT_COMMAND_ARGUMENT_SEPARATOR);
    }

    atCommand->_handler(atCommand, &args.base);

    ATCommand_SendResponse(
        AT_COMMAND_OK_RESPONSE,
        AT_COMMAND_OK_RESPONSE_LENGTH);
}

PRIVATE STATIC bool ATCommand_FindCallback(
    LinkedListNode *node,
    const void *data)
{
    ATCommand *command = LinkedListNode2ATCommand(node);

    if (node == NULL) {
        return false;
    }

    return (strncmp(command->_command, data, strlen(command->_command)) == 0);
}

PRIVATE STATIC bool ATCommand_SendResponse(const char *response, size_t length)
{
    return (BaseSerial_Write(serial, (const uint8_t *)response, length) != 0);
}
