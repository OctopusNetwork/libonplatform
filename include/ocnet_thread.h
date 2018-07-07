#ifndef __OCNET_THREAD____H__
#define __OCNET_THREAD____H__

#include <stdint.h>

struct ocnet_thread;
typedef struct ocnet_thread     ocnet_thread_t;

struct ocnet_mutex;
typedef struct ocnet_mutex      ocnet_mutex_t;

struct ocnet_cond;
typedef struct ocnet_cond       ocnet_cond_t;

#ifdef __cplusplus
extern "C" {
#endif

ocnet_thread_t *ocnet_thread_create(void *(*func)(void *), void *arg);
void            ocnet_thread_name_set(char *name);
int             ocnet_thread_join(ocnet_thread_t *thread);

ocnet_mutex_t  *ocnet_mutex_init(void);
int             ocnet_mutex_lock(ocnet_mutex_t *mutex);
int             ocnet_mutex_unlock(ocnet_mutex_t *mutex);
int             ocnet_mutex_destroy(ocnet_mutex_t *mutex);

ocnet_cond_t   *ocnet_cond_init(void);
int             ocnet_cond_wait(ocnet_cond_t *cond, ocnet_mutex_t *mutex);
int             ocnet_cond_timedwait(ocnet_cond_t *cond,
                    ocnet_mutex_t *mutex, int32_t milliseconds);
int             ocnet_cond_broadcast(ocnet_cond_t *cond);
int             ocnet_cond_signal(ocnet_cond_t *cond);
int             ocnet_cond_destroy(ocnet_cond_t *cond);

#ifdef __cplusplus
}
#endif

#endif
