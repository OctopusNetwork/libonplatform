#include <stdlib.h>
#include <stdio.h>

#include "ocnet_iport.h"

ocnet_ipvx_t ocnet_iport_get_ipvx_system(void)
{
    return OCNET_IPV4;
}

ocnet_ipvx_t ocnet_iport_get_ipvx_byip(ocnet_ip_t ip)
{
    return OCNET_IPV4;
}

ocnet_ip_t ocnet_iport_get_ip(void *iport)
{
    return 0;
}

ocnet_port_t ocnet_iport_get_port(void *iport)
{
    return 0;
}

void ocnet_iport_get_iport_desc(void *iport, char *str, int len)
{
}

ocnet_ip_t ocnet_iport_parse_ip(const char *str)
{
    return (127 << 24 | 1);
}

void ocnet_iport_ip_todesc(ocnet_ip_t ip, char *str, int len)
{
    sprintf(str, "%d.%d.%d.%d",
            ip >> 24 & 0xff,
            ip >> 16 & 0xff,
            ip >> 8 & 0xff,
            ip & 0xff);
}

void ocnet_iport_port_todesc(ocnet_port_t port, char *str, int len)
{
    sprintf(str, "%d", port);
}
