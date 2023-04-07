/**
 * TCP Server
 * Create a socket using socket()
 * Assign a port number to the socket with bind()
 * Allow connections to that port using listen()
 * Reapeat:
    Call accept() to get a new socket for each client connection
    communicate with client via new socket using send() and recv()
    close socket using close()
*/
#include "handle_clients.c"

#define MAX_CON_REQ 5 /* Maximum outstanding connection requests */

int main(int argc, char **argv){

    if(argc !=2) {
        fprintf(stderr,"Usage: %s <Server Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    u16 server_port = atoi(argv[1]);
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_sock <0) { exit_on_err("socket() failed"); }
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(server_port)
    };
    int bind_res = bind(server_sock, (struct sockaddr *) &server_addr,sizeof(server_addr));
    if(bind_res < 0) { exit_on_err("bind() failed"); }
    int lis_res = listen(server_sock, MAX_CON_REQ);
    if(lis_res <0) { exit_on_err("listen() failed"); }

    struct sockaddr_in client_addr;
    u32 client_addr_len;
    int client_sock;
    while(1) {
        client_addr_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_addr_len);
        if(client_sock < 0) { exit_on_err("accept() failed"); }
        /*client socket connection has been established*/
        printf("Handling clients %s\n",inet_ntoa(client_addr.sin_addr));
        // Handle TCP-Clients
        handle_tcp_clients(client_sock);
    }
    return EXIT_SUCCESS;
}