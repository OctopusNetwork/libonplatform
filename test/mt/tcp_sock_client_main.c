#include <stdio.h>

#include "ocnet_socket.h"
#include "ocnet_iport.h"
#include "ocnet_malloc.h"

int main(int argc, char *argv[])
{
    ocnet_socket_t ocnet_sock;
    ocnet_conn_t ocnet_conn;
    int recv_result = 0;
    char buf[1024] = {0};

    ocnet_sock = ocnet_socket_open(KKT_SOCK_TCP, 0, 10687);
    if (KKT_SOCKET_INVALID == ocnet_sock) {
        return -1;
    }

    ocnet_conn = ocnet_socket_connect(ocnet_sock,
            ocnet_iport_parse_ip("127.0.0.1"), 10688);
    if (ocnet_conn == KKT_CONN_INVALID) {
        ocnet_socket_close(ocnet_sock);
        return -1;
    } else {
        printf("Connect to: 127.0.0.1:10688\n");
    }

    if (ocnet_socket_send(ocnet_sock, ocnet_conn, "hello", 6) < 0) {
        ocnet_socket_close_connection(ocnet_sock, ocnet_conn);
        ocnet_socket_close(ocnet_sock);
        printf("Fail to write msg\n");
        return -1;
    }

    do {
        recv_result = ocnet_socket_recv(ocnet_sock,
                ocnet_conn, buf, sizeof(buf));
        if (0 < recv_result) {
            printf("Server msg: <%s>\n", buf);
            break;
        }
        usleep(100 * 1000);
    } while (1);

    ocnet_socket_close(ocnet_sock);
    return 0;
}
