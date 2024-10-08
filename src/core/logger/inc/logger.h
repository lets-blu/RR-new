#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define STATIC_LOGGER(name, level) {    \
    .base = STATIC_LINKED_LIST_NODE(),  \
    ._name = (name),                    \
    ._level = (level)                   \
}

#define LOGGER_D(self, format, args...) \
    PrintStringWithLogger(              \
        (self),                         \
        LOGGER_LEVEL_DEBUG,             \
        "[%s][D]" format "\r\n",        \
        (self)->_name, ##args)

#define LOGGER_I(self, format, args...) \
    PrintStringWithLogger(              \
        (self),                         \
        LOGGER_LEVEL_INFO,              \
        "[%s][I]" format "\r\n",        \
        (self)->_name, ##args)

#define LOGGER_W(self, format, args...) \
    PrintStringWithLogger(              \
        (self),                         \
        LOGGER_LEVEL_WARN,              \
        "[%s][W]" format "\r\n",        \
        (self)->_name, ##args)

#define LOGGER_E(self, format, args...) \
    PrintStringWithLogger(              \
        (self),                         \
        LOGGER_LEVEL_ERROR,             \
        "[%s][E]" format "\r\n",        \
        (self)->_name, ##args)

#define LinkedListNode2Logger(instance) \
    BASE2SUB(instance, Logger, base)

typedef enum {
    LOGGER_LEVEL_DEBUG,
    LOGGER_LEVEL_INFO,
    LOGGER_LEVEL_WARN,
    LOGGER_LEVEL_ERROR,
    LOGGER_LEVEL_OFF,
} LoggerLevel;

typedef struct {
    LinkedListNode base;
    const char *_name;
    LoggerLevel _level;
} Logger;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructLogger(
    Logger *instance,
    const char *name,
    LoggerLevel level);

PUBLIC void DestructLogger(Logger *instance);

// Public Method(s)
PUBLIC int PrintStringWithLogger(
    Logger *self,
    LoggerLevel level,
    const char *format,
    ...);

PUBLIC STATIC void RegisterLogger(Logger *instance);
PUBLIC STATIC void SetLevelToLogger(const char *name, LoggerLevel level);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LOGGER_H__
