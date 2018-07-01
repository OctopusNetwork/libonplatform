#ifndef __OCNET_THREAD____H__
#define __OCNET_THREAD____H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void          *ocnet_thread_create(void *(*func)(void *), void *arg);
void           ocnet_thread_name_set(char *name);
void          *ocnet_thread_self(void);

int            ocnet_thread_join(void *thread);

void          *ocnet_mutex_init(void);
int            ocnet_mutex_lock(void *mutex);
int            ocnet_mutex_unlock(void *mutex);
int            ocnet_mutex_destroy(void *mutex);

void          *ocnet_cond_init(void);
int            ocnet_cond_wait(void *cond, void *mutex);
int            ocnet_cond_timedwait(void *cond, void *mutex, int32_t milliseconds);
int            ocnet_cond_broadcast(void *cond);
int            ocnet_cond_signal(void *cond);
int            ocnet_cond_destroy(void *cond);

#ifdef __cplusplus
}
#endif

#endif
