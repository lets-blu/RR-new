#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"
#include "port/core/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef LOGGER_BUFFER_SIZE
#define LOGGER_BUFFER_SIZE 80U
#endif // LOGGER_BUFFER_SIZE

#define LOGGER_STATIC(name, level) {   \
    .base = LINKED_LIST_NODE_STATIC(), \
    ._name = (name),                   \
    ._level = (level),                 \
}

#define LOGGER_D(pThis, format, ...) \
    Logger_PrintF(                   \
        (pThis),                     \
        LOGGER_LEVEL_DEBUG,          \
        "[%s][D] " format "\r\n",    \
        (pThis)->_name, ##__VA_ARGS__)

#define LOGGER_I(pThis, format, ...) \
    Logger_PrintF(                   \
        (pThis),                     \
        LOGGER_LEVEL_INFO,           \
        "[%s][I] " format "\r\n",    \
        (pThis)->_name, ##__VA_ARGS__)

#define LOGGER_W(pThis, format, ...) \
    Logger_PrintF(                   \
        (pThis),                     \
        LOGGER_LEVEL_WARN,           \
        "[%s][W] " format "\r\n",    \
        (pThis)->_name, ##__VA_ARGS__)

#define LOGGER_E(pThis, format, ...) \
    Logger_PrintF(                   \
        (pThis),                     \
        LOGGER_LEVEL_ERROR,          \
        "[%s][E] " format "\r\n",    \
        (pThis)->_name, ##__VA_ARGS__)

#define LinkedListNode2Logger(pThis) \
    CONTAINER_OF(pThis, Logger, base)

typedef enum {
    LOGGER_LEVEL_DEBUG,
    LOGGER_LEVEL_INFO,
    LOGGER_LEVEL_WARN,
    LOGGER_LEVEL_ERROR,
} LoggerLevel;

typedef struct {
    LinkedListNode base;
    const char *_name;
    LoggerLevel _level;
} Logger;

// Constructor(s) & Destructor(s)
PUBLIC void Logger_Construct(
    Logger *pThis,
    const char *name,
    LoggerLevel level);

PUBLIC void Logger_Destruct(Logger *pThis);

// Public method(s)
PUBLIC int Logger_PrintF(
    Logger *pThis,
    LoggerLevel level,
    const char *format,
    ...);

PUBLIC STATIC void Logger_SetSerial(BaseSerial *newSerial);
PUBLIC STATIC void Logger_Register(Logger *logger);
PUBLIC STATIC void Logger_Deregister(Logger *logger);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LOGGER_H__
