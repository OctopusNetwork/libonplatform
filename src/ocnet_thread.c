#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "ocnet_malloc.h"
#include "ocnet_time.h"

#include "ocnet_thread.h"

void *ocnet_thread_create(void *(*func)(void *), void *arg)
{
    pthread_t *thread = ocnet_malloc(sizeof(pthread_t));

    if (pthread_create(thread, NULL, func, arg) < 0) {
        ocnet_free(thread);
        return NULL;
    }

    return thread;
}

int ocnet_thread_join(void *thread)
{
    int ret = 0;
    if (NULL == thread) {
        return -1;
    }
    ret = pthread_join(*(pthread_t *)thread, NULL);
    ocnet_free(thread);
    return ret;
}

void *ocnet_thread_self(void)
{
    return (void *)pthread_self();
}

void *ocnet_mutex_init(void)
{
    pthread_mutex_t *mutex = ocnet_malloc(sizeof(pthread_mutex_t));

    if (NULL == mutex) {
        return NULL;
    }
    pthread_mutex_init(mutex, NULL);
    return mutex;
}

int ocnet_mutex_lock(void *mutex)
{
    if (NULL == mutex) {
        return -1;
    }
    return pthread_mutex_lock((pthread_mutex_t *)mutex);
}

int ocnet_mutex_unlock(void *mutex)
{
    if (NULL == mutex) {
        return -1;
    }
    return pthread_mutex_unlock((pthread_mutex_t *)mutex);
}

int ocnet_mutex_destroy(void *mutex)
{
    if (NULL == mutex) {
        return -1;
    }

    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    ocnet_free(mutex);
    return 0;
}

void *ocnet_cond_init(void)
{
    pthread_cond_t *cond = ocnet_malloc(sizeof(pthread_cond_t));

    if (NULL == cond) {
        return NULL;
    }
    pthread_cond_init(cond, NULL);
    return cond;
}

int ocnet_cond_wait(void *cond, void *mutex)
{
    return pthread_cond_wait((pthread_cond_t *)cond,
            (pthread_mutex_t *)mutex);
}

int ocnet_cond_timedwait(void *cond, void *mutex, int32_t milliseconds)
{
    struct timespec ts;
    unsigned long now = ocnet_time_now(1);

    ts.tv_sec = (now + milliseconds) / 1000;
    ts.tv_nsec = ((now + milliseconds) % 1000) * 1000000;
    return pthread_cond_timedwait((pthread_cond_t *)cond,
            (pthread_mutex_t *)mutex, &ts);
}

int ocnet_cond_broadcast(void *cond)
{
    return pthread_cond_broadcast((pthread_cond_t *)cond);
}

int ocnet_cond_signal(void *cond)
{
    return pthread_cond_signal((pthread_cond_t *)cond);
}

int ocnet_cond_destroy(void *cond)
{
    if (NULL != cond) {
        pthread_cond_destroy((pthread_cond_t *)cond);
        ocnet_free(cond);
    }

    return 0;
}
