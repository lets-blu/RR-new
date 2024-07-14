#ifndef __BASE_FACTORY_H__
#define __BASE_FACTORY_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include "core/common/inc/Keywords.h"
#include "core/common/inc/LinkedList.h"
#include "port/common/inc/BasePort.h"

#define BASE_FACTORY_ANALOG_PORT    "DefaultAPort"
#define BASE_FACTORY_DIGITAL_PORT   "DefaultDPort"

#define LinkedListNode2BaseFactory(instance) \
    BASE2SUB(instance, BaseFactory, base)

struct BaseFactoryVtbl;

typedef struct {
    LinkedListNode base;
    const struct BaseFactoryVtbl *vtbl;
} BaseFactory;

typedef struct BaseFactoryVtbl {
    BasePort *(*CreatePort)(BaseFactory *, const char *, BasePortParameter *);
    void (*DestroyPort)(BaseFactory *, const char *, BasePort *);
} BaseFactoryVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructorBaseFactory(
    BaseFactory *instance);

PROTECTED void DestructorBaseFactory(
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

PUBLIC STATIC BasePort *CreatePortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePortParameter *parameter);

PUBLIC STATIC void DestroyPortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePort *port);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_FACTORY_H__
