#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#include "ocnet_malloc.h"

#include "ocnet_socket.h"

typedef struct {
    int             fd;
    ocnet_ip_t      ip;
    ocnet_port_t    port;

    unsigned short  sin_family;
    int             sock_type;
    int             protocol;
} ocnet_sockdesc_t;

ocnet_socket_t ocnet_socket_open(ocnet_socktype_t type,
        ocnet_ip_t ip, ocnet_port_t port)
{
    int fd = -1;
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    ocnet_sockdesc_t *sock_desc = NULL;
    int socktype;
    int protocol;

    char ip_desc[OCNET_MAX_IPORT_BUFLEN] = {0};
    char port_desc[OCNET_MAX_IPORT_BUFLEN] = {0};

    struct addrinfo hints, *res;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    socktype = (OCNET_SOCK_TCP == type) ? SOCK_STREAM : SOCK_DGRAM;
    protocol = (OCNET_SOCK_TCP == type) ? IPPROTO_TCP : IPPROTO_UDP;

    fd = socket(PF_INET, socktype, protocol);
    if (fd < 0) {
        return OCNET_SOCKET_INVALID;
    }

#ifdef SO_NOSIGPIPE
    setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &(int){1}, sizeof(int));
#endif

    ocnet_iport_ip_todesc(ip, ip_desc, OCNET_MAX_IPORT_BUFLEN);
    ocnet_iport_port_todesc(port, port_desc, OCNET_MAX_IPORT_BUFLEN);

    ocnet_memset(&hints, 0x0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    if (getaddrinfo(ip_desc, port_desc, &hints, &res) < 0) {
        goto L_ERROR_SOCK_GETADDRINFO;
    }

    if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {
        goto L_ERROR_SOCK_BIND;
    }

    freeaddrinfo(res);

    if (getsockname(fd, (struct sockaddr *)&addr, &len) < 0) {
        goto L_ERROR_SOCK_GETNAME;
    }

    sock_desc = (ocnet_sockdesc_t *)ocnet_malloc(
            sizeof(ocnet_sockdesc_t));
    if (NULL == sock_desc) {
        goto L_ERROR_SOCK_DESC_MALLOC;
    }

    sock_desc->fd = fd;
    sock_desc->ip = ntohl(addr.sin_addr.s_addr);
    sock_desc->port = ntohs(addr.sin_port);
    sock_desc->sin_family = AF_INET;
    sock_desc->sock_type = socktype;
    sock_desc->protocol = protocol;

    return (ocnet_socket_t)sock_desc;

L_ERROR_SOCK_DESC_MALLOC:
L_ERROR_SOCK_GETNAME:
L_ERROR_SOCK_BIND:
    freeaddrinfo(res);
L_ERROR_SOCK_GETADDRINFO:
    close(fd);
    return OCNET_SOCKET_INVALID;
}

ocnet_ip_t ocnet_socket_get_ip(ocnet_socket_t sock)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        return sock_desc->ip;
    }

    return 0;
}

ocnet_port_t ocnet_socket_get_port(ocnet_socket_t sock)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        return sock_desc->port;
    }

    return 0;
}

int ocnet_socket_get_fd(ocnet_socket_t sock)
{
    ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
    return sock_desc->fd;
}

void ocnet_socket_close(ocnet_socket_t sock)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        close(sock_desc->fd);
        ocnet_free(sock_desc);
    }
}

int ocnet_socket_listen(ocnet_socket_t sock, int backlog)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        if (OCNET_SOCK_TCP == sock_desc->sock_type) {
            return listen(sock_desc->fd, backlog);
        }
    }

    return -1;
}

ocnet_conn_t ocnet_socket_accept(ocnet_socket_t sock, ocnet_ip_t *ip, ocnet_port_t *port)
{
    ocnet_conn_t conn = OCNET_CONN_INVALID;

    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);

        conn = accept(sock_desc->fd, (struct sockaddr *)&addr, &addr_len);
        if (conn < 0) {
            return -1;
        }
        if (NULL != ip) {
            *ip = ntohl(addr.sin_addr.s_addr);
        }
        if (NULL != port) {
            *port = ntohs(addr.sin_port);
        }
    }

    return conn;
}

int ocnet_socket_close_connection(ocnet_socket_t sock, ocnet_conn_t conn)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        return close(conn);
    }
    return -1;
}

ocnet_conn_t ocnet_socket_connect(ocnet_socket_t sock, ocnet_ip_t ip, ocnet_port_t port)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);

        addr.sin_family = sock_desc->sin_family;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(ip);

        if (0 == connect(sock_desc->fd, (struct sockaddr *)&addr, addr_len)) {
            return (ocnet_conn_t)sock_desc->fd;
        }
    }

    return OCNET_CONN_INVALID;
}

int ocnet_socket_send(ocnet_socket_t sock, ocnet_conn_t conn, char *buf, size_t len)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        return send(conn, buf, len, 0);
    }

    return -1;
}

int ocnet_socket_sendto(ocnet_socket_t sock, char *buf, size_t len,
        ocnet_ip_t ip, ocnet_port_t port)
{
    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);

        addr.sin_family = sock_desc->sin_family;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(ip);

        return sendto(sock_desc->fd, buf, len, 0,
                (struct sockaddr *)&addr, addr_len);
    }

    return -1;
}

int ocnet_socket_recv(ocnet_socket_t sock, ocnet_conn_t conn, char *buf, size_t len)
{
    int recvlen = 0;

    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        recvlen = recv(conn, buf, len, MSG_DONTWAIT);
    }

    if (recvlen < 0) {
        if (EAGAIN == errno || EWOULDBLOCK == errno) {
            return 0;
        }
    }

    if (0 == recvlen) {
        return -1;
    }

    return recvlen;
}

int ocnet_socket_recvfrom(ocnet_socket_t sock, char *buf, size_t len,
        ocnet_ip_t *ip, ocnet_port_t *port)
{
    int result = -1;

    if (NULL != sock && OCNET_SOCKET_INVALID != sock) {
        ocnet_sockdesc_t *sock_desc = (ocnet_sockdesc_t *)sock;
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);

        result = recvfrom(sock_desc->fd, buf, len, 0,
                (struct sockaddr *)&addr, &addr_len);
        if (0 < result) {
            if (NULL != ip) {
                *ip = ntohl(addr.sin_addr.s_addr);
            }
            if (NULL != port) {
                *port = ntohs(addr.sin_port);
            }
        }
    }

    return result;
}
