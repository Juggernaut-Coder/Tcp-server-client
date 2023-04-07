#include "../inc/inc.h"

void handle_tcp_clients(int);

void handle_tcp_clients(int sock) {
    char buf[buf_size];
    ssize_t recv_msg_size = recv(sock, buf, buf_size, 0);
    printf("Client Message: %s", buf);
    while(recv_msg_size > 0) { /* greater than zero indicates end of reception */
        ssize_t sent_bytes = send(sock,buf,recv_msg_size,0);
        if(sent_bytes != recv_msg_size) {
            exit_on_err("sent() input-output byte mistach");
        }
        recv_msg_size = recv(sock, buf, buf_size, 0);
        if(recv_msg_size < 0) { exit_on_err("recv() failed"); }
    }
    close(sock);
}