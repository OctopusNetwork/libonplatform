#include <string.h>

#include "ocnet_string.h"

char *ocnet_strncpy(char *dest, char *src, int n)
{
    return strncpy(dest, src, n);
}

int ocnet_strlen(char *str)
{
    return strlen(str);
}
