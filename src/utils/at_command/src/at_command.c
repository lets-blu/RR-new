#include "utils/at_command/inc/at_command.h"

// Private member(s)
PRIVATE STATIC LinkedList commands = STATIC_LINKED_LIST();

// Private method(s)
PRIVATE void SendResponseATCommand(ATCommand *self, const char *responseString);

PRIVATE STATIC bool FindCallbackOfATCommand(
    LinkedListNode *node,
    const void *data);

// Method implement(s)
PUBLIC void ConstructATCommand(
    ATCommand *instance,
    const char *command,
    ATCommandCallback callback)
{
    if (instance == NULL || command == NULL || callback == NULL)
    {
        return;
    }

    ConstructLinkedListNode(&instance->base);
    instance->_command = command;
    instance->_callback = callback;

    RegisterATCommand(instance);
}

PUBLIC void DestructATCommand(ATCommand *instance)
{
    if (instance != NULL)
    {
        UnregisterATCommand(instance);
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(ATCommand));
    }
}

PUBLIC void ResponseATCommand(ATCommand *self, const char *responseString)
{
    unsigned int length = 0;
    char buffer[AT_COMMAND_MAX_LENGTH] = {0};

    if (self == NULL || responseString == NULL)
    {
        return;
    }

    strcpy(buffer, self->_command);
    length += strlen(self->_command);

    buffer[length++] = ':';

    strcpy(buffer + length, responseString);
    length += strlen(responseString);

    buffer[length++] = '\r';

    SendResponseATCommand(self, buffer);
}

PRIVATE void SendResponseATCommand(ATCommand *self, const char *responseString)
{
    (void)self;
    puts(responseString);
}

PUBLIC STATIC void RegisterATCommand(ATCommand *instance)
{
    if (instance != NULL
        && FindNodeInLinkedList(
            &commands,
            FindCallbackOfATCommand,
            (void *)instance->_command) == NULL)
    {
        AddNodeToLinkedList(&commands, &instance->base);
    }
}

PUBLIC STATIC void UnregisterATCommand(ATCommand *instance)
{
    if (instance != NULL)
    {
        RemoveNodeFromLinkedList(&commands, &instance->base);
    }
}

PUBLIC STATIC void RingBufferCallbackOfATCommand(
    RingBufferEvent event,
    RingBufferEventParameter *parameter)
{
    RingBufferPacketResult result = {0};
    uint8_t buffer[AT_COMMAND_MAX_LENGTH] = {0};

    RingBufferPacketParameter packetParameter = {
        .header = (uint8_t *)AT_COMMAND_HEADER,
        .headerLength = AT_COMMAND_HEADER_LENGTH,
        .footer = (uint8_t *)AT_COMMAND_FOOTER,
        .footerLength = AT_COMMAND_FOOTER_LENGTH
    };

    if (event != RING_BUFFER_EVENT_READY_TO_READ)
    {
        return;
    }

    result = FindPacketInRingBuffer(parameter->buffer, &packetParameter);

    if (result.invalidLength != 0)
    {
        ReadRingBuffer(parameter->buffer, buffer, result.invalidLength);
    }

    if (result.packetLength != 0)
    {
        ReadRingBuffer(parameter->buffer, buffer, result.packetLength);
        ProcessATCommand((char *)buffer);
    }
}

PUBLIC STATIC void ProcessATCommand(char *commandString)
{
    ATCommand *command = NULL;

    char *end = NULL;
    char *parameters = NULL;
    const char *parameter = NULL;

    unsigned int argc = 1;
    const char *argv[AT_COMMAND_MAX_PARAMETERS_NUMBER] = {commandString};

    // 1. Check parameters
    if (commandString == NULL)
    {
        return;
    }

    // 2. Find command
    command = LinkedListNode2ATCommand(FindNodeInLinkedList(
            &commands,
            FindCallbackOfATCommand,
            (void *)(commandString + AT_COMMAND_HEADER_LENGTH)));

    if (command == NULL)
    {
        SendResponseATCommand(command, "ERROR");
        return;
    }

    // 3. Remove footer
    end = strchr(commandString, '\r');

    if (end != NULL)
    {
        *end = '\0';
    }

    // 4. If there is no parameter
    parameters = strchr(commandString, '=');

    if (parameters == NULL)
    {
        command->_callback(argc, argv);
        SendResponseATCommand(command, "OK");
        return;
    }

    // 5. If there is parameter
    *parameters = '\0';
    parameter = strtok(parameters + 1, ",");

    while (parameter != NULL && argc < AT_COMMAND_MAX_PARAMETERS_NUMBER)
    {
        argv[argc++] = parameter;
        parameter = strtok(NULL, ",");
    }

    command->_callback(argc, argv);
    SendResponseATCommand(command, "OK");
}

PRIVATE STATIC bool FindCallbackOfATCommand(
    LinkedListNode *node,
    const void *data)
{
    ATCommand *command = LinkedListNode2ATCommand(node);
    return (strncmp(command->_command, data, strlen(command->_command)) == 0);
}
