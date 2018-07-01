#ifndef __OCNET_TIME___H__
#define __OCNET_TIME___H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int            ocnet_time_initialize(int cacheable);

uint64_t       ocnet_time_now(int cached_time);
uint64_t       ocnet_time_now_tostring(int cached_time, char *buf, int *len);
void           ocnet_time_finalize(void);
void           ocnet_msleep(int milliseconds);

#ifdef __cplusplus
}
#endif

#endif
