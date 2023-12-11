#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 0x10000

inline size_t __attribute__((__always_inline__)) get_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long ms = tv.tv_sec;
    return ms * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char *message = malloc(BUF_SIZE);
    double elapsed_time;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() error!");
    }
    printf("[*] socket created\n");

    memset(&serv_addr, 0, sizeof(serv_addr));       // initialize serv_addr to 0
    serv_addr.sin_family = AF_INET;                 // IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 32bit IPv4 address
    serv_addr.sin_port = htons(atoi(argv[2]));      // port number

    printf("[*] connecting to %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
    if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("connect() error!");
    }
    printf("[*] connected\n");
    double elapsed_time_sum = 0;
    
    for (int i = 0; i < 0x100; i++) {
        size_t start_t = get_ms();
        write(sock, message, 0x40);
        int r = read(sock, message, 0x40);
        size_t end_t = get_ms();
        if (r == -1) {
            perror("read() error!");
        }
        // elapsed_time in ms
        elapsed_time = (double) (end_t - start_t);
        elapsed_time_sum += elapsed_time;
    }
    printf("[*] average elapsed time: %f\n", elapsed_time_sum / 0x100);
    close(sock);
    return 0;
}

