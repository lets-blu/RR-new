#ifndef __BASE_FACTORY_H__
#define __BASE_FACTORY_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#include "port/common/inc/base_port.h"
#include "port/common/inc/base_serial.h"
#include "port/common/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LinkedListNode2BaseFactory(instance) \
    BASE2SUB(instance, BaseFactory, base)

struct BaseFactoryVtbl;

typedef struct {
    LinkedListNode base;
    const struct BaseFactoryVtbl *vtbl;
} BaseFactory;

typedef struct BaseFactoryVtbl {
    BasePort *(*CreatePort)(
        BaseFactory *self,
        const char *type,
        BasePortParameter *parameter);

    void (*DestroyPort)(
        BaseFactory *self,
        const char *type,
        BasePort *port);

    BaseSerial *(*CreateSerial)(
        BaseFactory *self,
        const char *type,
        BaseSerialParameter *parameter);

    void (*DestroySerial)(
        BaseFactory *self,
        const char *type,
        BaseSerial *serial);

    BaseTask *(*CreateTask)(
        BaseFactory *self,
        const char *type,
        BaseTaskParameter *parameter);

    void (*DestroyTask)(
        BaseFactory *self,
        const char *type,
        BaseTask *task);
} BaseFactoryVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseFactory(
    BaseFactory *instance);

PROTECTED void DestructBaseFactory(
    BaseFactory *instance);

// Public method(s)
PUBLIC BasePort *CreatePortWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void DestroyPortWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BasePort *port);

PUBLIC BaseSerial *CreateSerialWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void DestroySerialWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseSerial *serial);

PUBLIC BaseTask *CreateTaskWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void DestroyTaskWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseTask *task);

PUBLIC STATIC BasePort *CreatePortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePortParameter *parameter);

PUBLIC STATIC void DestroyPortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePort *port);

PUBLIC STATIC BaseSerial *CreateSerialWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC STATIC void DestroySerialWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseSerial *serial);

PUBLIC STATIC BaseTask *CreateTaskWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC STATIC void DestroyTaskWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseTask *task);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_FACTORY_H__
