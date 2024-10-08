#include "core/logger/inc/logger.h"

// Private member(s)
PRIVATE STATIC LinkedList loggers = STATIC_LINKED_LIST();

// Private method(s)
PRIVATE STATIC bool FindCallbackOfLogger(LinkedListNode *node, void *data);

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
        AddNodeToLinkedList(&loggers, &instance->base);
    }
}

PUBLIC void DestructLogger(Logger *instance)
{
    if (instance != NULL)
    {
        RemoveNodeFromLinkedList(&loggers, &instance->base);
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
    if (FindNodeInLinkedList(
            &loggers,
            FindCallbackOfLogger,
            (void *)instance->_name) == NULL)
    {
        AddNodeToLinkedList(&loggers, &instance->base);
    }
}

PUBLIC STATIC void SetLevelToLogger(const char *name, LoggerLevel level)
{
    LinkedListNode *node
        = FindNodeInLinkedList(&loggers, FindCallbackOfLogger, (void *)name);

    if (node != NULL)
    {
        LinkedListNode2Logger(node)->_level = level;
    }
}

PRIVATE STATIC bool FindCallbackOfLogger(LinkedListNode *node, void *data)
{
    return (strcmp(LinkedListNode2Logger(node)->_name, data) == 0);
}
