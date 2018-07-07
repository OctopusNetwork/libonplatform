#ifndef __OCNET_IPORT____H__
#define __OCNET_IPORT____H__

#include <stdint.h>

typedef uint32_t ocnet_ip_t;
typedef uint16_t ocnet_port_t;

#define OCNET_MAX_IPORT_BUFLEN        32

typedef enum {
    OCNET_IPV4 = 0x01,
    OCNET_IPV6 = 0x02
} ocnet_ipvx_t;

#ifdef __cplusplus
extern "C" {
#endif

ocnet_ipvx_t ocnet_iport_get_ipvx_system(void);
ocnet_ipvx_t ocnet_iport_get_ipvx_byip(ocnet_ip_t ip);
ocnet_ip_t   ocnet_iport_get_ip(void *iport);
ocnet_port_t ocnet_iport_get_port(void *iport);
void         ocnet_iport_get_iport_desc(void *iport, char *str, int len);
ocnet_ip_t   ocnet_iport_parse_ip(const char *str);
void         ocnet_iport_ip_todesc(ocnet_ip_t ip, char *str, int len);
void         ocnet_iport_port_todesc(ocnet_port_t port, char *str, int len);

#ifdef __cplusplus
}
#endif

#endif
