/** 
 * TCP Client Program
 * Takes 3 input Server IP, Sever Port(optional), communication string 
 * Create TCP socket using socket().
 * Establish a connection to the server using connect().
 * Communicate using send() and recv().
 * Close the connection with close().
*/
#include "../inc/inc.h"
int main (int argc, char **argv) {
    /* Check if number of arguments */
    if(argc < 3 || argc > 4) {
        fprintf(stderr,"Usage: %s <Server IP> <Communication String> <Port Number (optional)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Parse arguments */
    char *server_ip = argv[1]; /* dotted quad address */
    char *comms_str = argv[2]; /* message to send */
    u16 port = (argc==4)? atoi(argv[3]) : 7;
    /* Create a Socket using TCP protocol and validate socket */
    int sock_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_id < 0) { exit_on_err("socket() failed"); }
    /* Construct the server address structure */
    struct sockaddr_in server_addr = { 
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr= inet_addr(server_ip)
    };
    /* Establish connection to the server */
    int con_res = connect(
        sock_id, 
        (struct sockaddr *) &server_addr, 
        sizeof(server_addr)
    );
    if(con_res < 0) { exit_on_err("connect() failed"); }
    /* Send communication string the server*/
    ssize_t comms_strlen = (ssize_t)strlen(comms_str);
    if(send(sock_id,comms_str,comms_strlen, 0) != comms_strlen)
        { exit_on_err("in sent() input output bytes mismatch"); }
    /* Recieve the communication string back from the server */
    int total_bytes_recv = 0;
    char buf[buf_size];
    while(total_bytes_recv < comms_strlen) {
        ssize_t bytes_recv = recv(sock_id,buf,buf_size-1,0);
        if(bytes_recv <= 0)
            { exit_on_err("recv() failed or connection closed prematurely"); }
        total_bytes_recv += bytes_recv;
        buf[bytes_recv] = '\0';
    }
    /* Print the string recieved */
    printf("Echoed Messgae from server:%s\n",buf);
    /* Close the socket */
    close(sock_id);
    return EXIT_SUCCESS;
}