#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ocnet_malloc.h"

void *ocnet_malloc(size_t size)
{
    return malloc(size);
}

void ocnet_free(void *ptr)
{
    free(ptr);
}

void ocnet_memset(void *ptr, char val, size_t size)
{
    memset(ptr, val, size);
}

void *ocnet_memcpy(void *dest, void *src, size_t size)
{
    return memcpy(dest, src, size);
}
