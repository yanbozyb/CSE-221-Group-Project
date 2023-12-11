#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 0x10000
#define PORT 8787

inline size_t __attribute__((__always_inline__)) get_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long ms = tv.tv_sec;
    return ms * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char* argv[]) {
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        perror("socket() error!");
    }
    printf("[*] socket created\n");
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

    while(1) {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        close(clnt_sock);
        shutdown(clnt_sock, SHUT_RDWR);
    }
    return 0;
}

