#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "ocnet_malloc.h"
#include "ocnet_time.h"

#include "ocnet_thread.h"

struct ocnet_thread {
    pthread_t       thread;
};

struct ocnet_mutex {
    pthread_mutex_t mutex;
};

struct ocnet_cond {
    pthread_cond_t  cond;
};

ocnet_thread_t *ocnet_thread_create(void *(*func)(void *), void *arg)
{
    ocnet_thread_t *thread = ocnet_malloc(sizeof(ocnet_thread_t));

    if (NULL == thread) {
        return NULL;
    }

    if (pthread_create(&thread->thread, NULL, func, arg) < 0) {
        ocnet_free(thread);
        return NULL;
    }

    return thread;
}

int ocnet_thread_join(ocnet_thread_t *thread)
{
    int ret = 0;
    ret = pthread_join(thread->thread, NULL);
    ocnet_free(thread);
    return ret;
}

ocnet_mutex_t *ocnet_mutex_init(void)
{
    ocnet_mutex_t *mutex = ocnet_malloc(sizeof(ocnet_mutex_t));

    if (NULL == mutex) {
        return NULL;
    }
    pthread_mutex_init(&mutex->mutex, NULL);
    return mutex;
}

int ocnet_mutex_lock(ocnet_mutex_t *mutex)
{
    return pthread_mutex_lock(&mutex->mutex);
}

int ocnet_mutex_unlock(ocnet_mutex_t *mutex)
{
    return pthread_mutex_unlock(&mutex->mutex);
}

int ocnet_mutex_destroy(ocnet_mutex_t *mutex)
{
    pthread_mutex_destroy(&mutex->mutex);
    ocnet_free(mutex);
    return 0;
}

ocnet_cond_t *ocnet_cond_init(void)
{
    ocnet_cond_t *cond = ocnet_malloc(sizeof(ocnet_cond_t));

    if (NULL == cond) {
        return NULL;
    }
    pthread_cond_init(&cond->cond, NULL);
    return cond;
}

int ocnet_cond_wait(ocnet_cond_t *cond, ocnet_mutex_t *mutex)
{
    return pthread_cond_wait(&cond->cond, &mutex->mutex);
}

int ocnet_cond_timedwait(ocnet_cond_t *cond,
        ocnet_mutex_t *mutex, int32_t milliseconds)
{
    struct timespec ts;
    unsigned long now = ocnet_time_now(1);

    ts.tv_sec = (now + milliseconds) / 1000;
    ts.tv_nsec = ((now + milliseconds) % 1000) * 1000000;
    return pthread_cond_timedwait(&cond->cond,
            &mutex->mutex, &ts);
}

int ocnet_cond_broadcast(ocnet_cond_t *cond)
{
    return pthread_cond_broadcast(&cond->cond);
}

int ocnet_cond_signal(ocnet_cond_t *cond)
{
    return pthread_cond_signal(&cond->cond);
}

int ocnet_cond_destroy(ocnet_cond_t *cond)
{
    pthread_cond_destroy(&cond->cond);
    ocnet_free(cond);
    return 0;
}
