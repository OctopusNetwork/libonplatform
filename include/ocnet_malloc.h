#ifndef __OCNET_MALLOC____H__
#define __OCNET_MALLOC____H__

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void    *ocnet_malloc(size_t size);
void     ocnet_free(void *ptr);
void     ocnet_memset(void *ptr, char val, size_t size);
void    *ocnet_memcpy(void *desc, void *src, size_t size);

#ifdef __cplusplus
}
#endif

#endif
