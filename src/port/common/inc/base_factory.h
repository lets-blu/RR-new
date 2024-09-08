#ifndef __BASE_FACTORY_H__
#define __BASE_FACTORY_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#include "port/common/inc/base_port.h"
#include "port/common/inc/base_task.h"

#define LinkedListNode2BaseFactory(instance) \
    BASE2SUB(instance, BaseFactory, base)

struct BaseFactoryVtbl;

typedef struct {
    LinkedListNode base;
    const struct BaseFactoryVtbl *vtbl;
} BaseFactory;

typedef struct BaseFactoryVtbl {
    BasePort *(*CreatePort)(
        BaseFactory *,
        const char *,
        BasePortParameter *);

    void (*DestroyPort)(
        BaseFactory *,
        const char *,
        BasePort *);

    BaseTask *(*CreateTask)(
        BaseFactory *,
        const char *,
        BaseTaskParameter *);

    void (*DestroyTask)(
        BaseFactory *,
        const char *,
        BaseTask *);
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
