#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define EVENT_ARGS_RESERVED 0U

typedef struct {
    unsigned int _reserved;
} EventArgs;

typedef void (*EventHandler)(void *, EventArgs *);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __EVENT_HANDLER_H__
