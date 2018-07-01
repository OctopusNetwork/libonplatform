#include "ocnet_time.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include <sys/time.h>
#include <inttypes.h>

static uint64_t __now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
}

static uint64_t __now_str(char *buf, int *len)
{
    struct timeval tv;
    time_t s;
    struct tm local, utc;
    int time_zone = 0;

    gettimeofday(&tv, NULL);
    time(&s);
    gmtime_r(&s, &utc);
    localtime_r(&s, &local);
    time_zone = local.tm_hour - utc.tm_hour;

    if (time_zone < -12) {
        time_zone += 24;
    } else if (12 < time_zone) {
        time_zone -= 24;
    }

    *len = sprintf(buf, "%4d-%d-%02d %02d:%02d:%02d.%06"PRId64"(UTC%+d)",
            local.tm_year + 1900,
            local.tm_mon + 1,
            local.tm_mday,
            local.tm_hour,
            local.tm_min,
            local.tm_sec,
            (int64_t)tv.tv_usec,
            time_zone);

    return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
}

int ocnet_time_initialize(int cacheable)
{
    if (0 != cacheable) {
        /* TODO: If the result is cacheable, we use a thread to manage the time */
    }

    return 0;
}

void ocnet_time_finalize(void)
{
}

uint64_t ocnet_time_now(int cached_time)
{
    return __now();
}

uint64_t ocnet_time_now_tostring(int cached_time, char *buf, int *len)
{
    return __now_str(buf, len);
}

void ocnet_msleep(int milliseconds)
{
    struct timespec tp;
    time_t seconds = (int)(milliseconds / 1000);
    tp.tv_sec = seconds;
    tp.tv_nsec = (long)(milliseconds - (seconds * 1000)) * 1000000L;
    nanosleep(&tp, NULL);
}
