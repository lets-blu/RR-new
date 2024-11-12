#include "core/logger/inc/logger.h"

// Private method(s)
PRIVATE STATIC bool FindCallbackOfLogger(
    LinkedListNode *node,
    const void *data);

PRIVATE STATIC void CommandCallbackOfLogger(
    unsigned int argc,
    const char *argv[]);

// Private member(s)
PRIVATE STATIC const char *levelString[] = {
    "DEBUG", "INFO", "WARN", "ERROR", "OFF"
};

PRIVATE STATIC LinkedList loggers = STATIC_LINKED_LIST();

PRIVATE STATIC ATCommand command
    = STATIC_AT_COMMAND("+LOGGER", CommandCallbackOfLogger);

// Method implement(s)
PUBLIC void ConstructLogger(
    Logger *instance,
    const char *name,
    LoggerLevel level)
{
    if (instance != NULL)
    {
        instance->_name = name;
        instance->_level = level;
        RegisterLogger(instance);
    }
}

PUBLIC void DestructLogger(Logger *instance)
{
    if (instance != NULL)
    {
        UnregisterLogger(instance);
        memset(instance, 0, sizeof(Logger));
    }
}

PUBLIC int PrintStringWithLogger(
    Logger *self,
    LoggerLevel level,
    const char *format,
    ...)
{
    va_list args;
    int result = 0;

    if (self != NULL && self->_level <= level)
    {
        va_start(args, format);
        result = vprintf(format, args);
        va_end(args);
    }

    return result;
}

PUBLIC STATIC void RegisterLogger(Logger *instance)
{
    if (instance == NULL)
    {
        return;
    }

    RegisterATCommand(&command);

    if (FindNodeInLinkedList(
            &loggers,
            FindCallbackOfLogger,
            (void *)instance->_name) == NULL)
    {
        AddNodeToLinkedList(&loggers, &instance->base);
    }
}

PUBLIC STATIC void UnregisterLogger(Logger *instance)
{
    if (instance != NULL)
    {
        RemoveNodeFromLinkedList(&loggers, &instance->base);
    }
}

PUBLIC STATIC bool SetLevelToLogger(const char *name, LoggerLevel level)
{
    LinkedListNode *node
        = FindNodeInLinkedList(&loggers, FindCallbackOfLogger, (void *)name);

    if (node == NULL)
    {
        return false;
    }

    LinkedListNode2Logger(node)->_level = level;
    return true;
}

PRIVATE STATIC bool FindCallbackOfLogger(
    LinkedListNode *node,
    const void *data)
{
    return (strcmp(LinkedListNode2Logger(node)->_name, data) == 0);
}

PRIVATE STATIC void CommandCallbackOfLogger(
    unsigned int argc,
    const char *argv[])
{
    if (argc < LOGGER_PARAMETERS_NUMBER)
    {
        ResponseATCommand(&command, "Invalid parameters");
        return;
    }

    for (unsigned int i = 0; i < NUMBER_OF_LOGGER_LEVELS; i++)
    {
        if (strcmp(argv[LOGGER_PARAMETER_LEVEL], levelString[i]) != 0)
        {
            continue;
        }

        if (!SetLevelToLogger(argv[LOGGER_PARAMETER_NAME], (LoggerLevel)i))
        {
            ResponseATCommand(&command, "Unkown name");
        }

        return;
    }

    ResponseATCommand(&command, "Unkown level");
}
