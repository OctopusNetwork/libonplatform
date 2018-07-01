#ifndef __OCNET_SOCKET____H__
#define __OCNET_SOCKET____H__

#include <unistd.h>

#include "ocnet_iport.h"

typedef void * ocnet_socket_t;
typedef int ocnet_conn_t;

#define OCNET_SOCKET_INVALID      ((ocnet_socket_t)(-1))
#define OCNET_CONN_INVALID        ((ocnet_conn_t)(-1))

typedef enum {
    OCNET_SOCK_UDP,
    OCNET_SOCK_TCP,
    OCNET_SOCK_RAW
} ocnet_socktype_t;

#ifdef __cplusplus
extern "C" {
#endif

ocnet_socket_t  ocnet_socket_open(ocnet_socktype_t, ocnet_ip_t ip, ocnet_port_t port);

ocnet_ip_t      ocnet_socket_get_ip(ocnet_socket_t sock);
ocnet_port_t    ocnet_socket_get_port(ocnet_socket_t sock);
int             ocnet_socket_get_fd(ocnet_socket_t sock);

void            ocnet_socket_close(ocnet_socket_t sock);

/* Connect-less mode */
int ocnet_socket_recvfrom(ocnet_socket_t sock, char *buf, size_t len,
                ocnet_ip_t *ip, ocnet_port_t *port);
int ocnet_socket_sendto(ocnet_socket_t sock, char *buf, size_t len,
                ocnet_ip_t ip, ocnet_port_t port);
/* Connect mode */
int ocnet_socket_send(ocnet_socket_t sock, ocnet_conn_t conn, char *buf, size_t len);
int ocnet_socket_recv(ocnet_socket_t sock, ocnet_conn_t conn, char *buf, size_t len);
int ocnet_socket_listen(ocnet_socket_t sock, int backlog);
ocnet_conn_t ocnet_socket_accept(ocnet_socket_t sock, ocnet_ip_t *ip, ocnet_port_t *port);
ocnet_conn_t ocnet_socket_connect(ocnet_socket_t sock, ocnet_ip_t ip, ocnet_port_t port);
int ocnet_socket_close_connection(ocnet_socket_t sock, ocnet_conn_t conn);

#ifdef __cplusplus
}
#endif

#endif
