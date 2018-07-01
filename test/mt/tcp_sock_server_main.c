#include <stdio.h>

#include "ocnet_socket.h"
#include "ocnet_iport.h"
#include "ocnet_malloc.h"

int main(int argc, char *argv[])
{
    ocnet_socket_t ocnet_sock;
    ocnet_ip_t ip;
    ocnet_port_t port;
    ocnet_conn_t ocnet_conn = 0;
    int recv_result = 0;
    char buf[1024] = {0};

    ocnet_sock = ocnet_socket_open(KKT_SOCK_TCP, 0, 10688);
    if (KKT_SOCKET_INVALID == ocnet_sock) {
        return -1;
    }

    if (ocnet_socket_listen(ocnet_sock, 1000) < 0) {
        ocnet_socket_close(ocnet_sock);
        return -1;
    }

    ocnet_conn = ocnet_socket_accept(ocnet_sock, &ip, &port);
    if (KKT_CONN_INVALID != ocnet_conn) {
        printf("Connect from: %d.%d.%d.%d:%d\n",
                ip >> 24 & 0xff, ip >> 16 & 0xff,
                ip >> 8 & 0xff, ip & 0xff, port);
    } else {
        ocnet_socket_close(ocnet_sock);
        return -1;
    }

    do {
        recv_result = ocnet_socket_recv(ocnet_sock,
                ocnet_conn, buf, sizeof(buf));
        if (0 < recv_result) {
            printf("Client msg: <%s>\n", buf);
            ocnet_socket_send(ocnet_sock, ocnet_conn, "world", 6);
            break;
        }
        usleep(100 * 1000);
    } while (1);

    ocnet_socket_close_connection(ocnet_sock, ocnet_conn);
    ocnet_socket_close(ocnet_sock);
    return 0;
}
