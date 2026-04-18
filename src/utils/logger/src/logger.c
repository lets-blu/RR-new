#include "utils/logger/inc/logger.h"

// Private member(s)
PRIVATE STATIC BaseSerial *serial = NULL;
PRIVATE STATIC LinkedList loggers = LINKED_LIST_STATIC();

// Private method(s)
PRIVATE STATIC bool Logger_FindCallback(LinkedListNode *node, const void *data);

// Method implement(s)
PUBLIC void Logger_Construct(
    Logger *pThis,
    const char *name,
    LoggerLevel level)
{
    if (pThis != NULL) {
        LinkedListNode_Construct(&pThis->base);
        pThis->_name = name;
        pThis->_level = level;
    }
}

PUBLIC void Logger_Destruct(Logger *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(Logger));
    }
}

PUBLIC int Logger_PrintF(
    Logger *pThis,
    LoggerLevel level,
    const char *format,
    ...)
{
    va_list args;
    int length = 0;
    char buffer[LOGGER_BUFFER_SIZE] = {0};

    if (pThis != NULL && pThis->_level <= level) {
        va_start(args, format);
        length = vsnprintf(buffer, LOGGER_BUFFER_SIZE, format, args);
        va_end(args);
    }

    return BaseSerial_Write(serial, (const uint8_t *)buffer, length);
}

PUBLIC STATIC void Logger_SetSerial(BaseSerial *newSerial)
{
    serial = newSerial;
}

PUBLIC STATIC void Logger_Register(Logger *logger)
{
    if (logger == NULL) {
        return;
    }

    if (LinkedList_FindNode(&loggers, Logger_FindCallback, logger) == NULL) {
        LinkedList_AddTail(&loggers, &logger->base);
    }
}

PUBLIC STATIC void Logger_Deregister(Logger *logger)
{
    if (logger != NULL) {
        LinkedList_RemoveNode(&loggers, &logger->base);
    }
}

PRIVATE STATIC bool Logger_FindCallback(LinkedListNode *node, const void *data)
{
    return (node == NULL) ? false : (LinkedListNode2Logger(node) == data);
}
