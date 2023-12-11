#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"

#define PORT 8787

inline size_t __attribute__((__always_inline__)) get_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long ms = tv.tv_sec;
    return ms * 1000 + tv.tv_usec / 1000;
}

int main () {
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    char *message = malloc(BUF_SIZE);
    int str_len;
    int opt = 1;

    // set socket, force bind to PORT
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock <= 0) {
        perror("socket() error!");
    }

    // Forcefully attaching socket to the port
    if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));       // initialize serv_addr to 0
    serv_addr.sin_family = AF_INET;                 // IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 32bit IPv4 address
    serv_addr.sin_port = htons(PORT);               // port number

    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind() error!");
    }

    if (listen(serv_sock, 5) == -1) {
        perror("listen() error!");
    }

    printf("[*] listening on %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        perror("accept() error!");
    }
    while (1) {
        str_len = recv(clnt_sock, message, BUF_SIZE, 0);
        if (str_len == 0) {
            break;
        }
        send(clnt_sock, message, str_len, 0);
        printf("[*] reply \n");
    }

    close(clnt_sock);
    close(serv_sock);

    return 0;
}