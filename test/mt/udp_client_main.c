#include <stdio.h>

#include "ocnet_socket.h"
#include "ocnet_iport.h"
#include "ocnet_malloc.h"

int main(int argc, char *argv[])
{
    ocnet_socket_t *ocnet_sock;
    char buf[1024] = {0};
    ocnet_ip_t ip;
    ocnet_port_t port;
    int recv_result = 0;

    ocnet_sock = ocnet_socket_open(OCNET_SOCK_UDP, 0, 10687);
    if (NULL == ocnet_sock) {
        return -1;
    }

    ocnet_socket_sendto(ocnet_sock, "hello", 6,
            ocnet_iport_parse_ip("127.0.0.1"), 10688);

    do {
        recv_result = ocnet_socket_recvfrom(ocnet_sock,
                buf, 1024, &ip, &port);
        if (0 < recv_result) {
            printf("Recv from: %d.%d.%d.%d:%d <%s>\n",
                    ip >> 24 & 0xff, ip >> 16 & 0xff,
                    ip >> 8 & 0xff, ip & 0xff,
                    port, buf);
            break;
        }

        usleep(20 * 1000 * 1000);
    } while (1);

    ocnet_socket_close(ocnet_sock);
    return 0;
}
