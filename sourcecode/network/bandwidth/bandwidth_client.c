#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"
#include <fcntl.h>

inline size_t __attribute__((__always_inline__)) get_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long ms = tv.tv_sec;
    return ms * 1000 + tv.tv_usec / 1000;
}

int block_socket(int fd, int blocking) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return 0;
    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    return (fcntl(fd, F_SETFL, flags) == 0) ? 1 : 0;
}

int main(int argc, char* argv[]) {
    // measure bandwidth
    int sock;
    struct sockaddr_in serv_addr;
    char *message = malloc(BUF_SIZE);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() error!");
    }
    printf("[*] socket created\n");

    if (!block_socket(sock, 1)) {
        printf("[-] failed to set blocking socket\n");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));   // initialize serv_addr to 0
    serv_addr.sin_family = AF_INET;                 // IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 32bit IPv4 address
    serv_addr.sin_port = htons(atoi(argv[2]));      // port number

    printf("[*] connecting to %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
    if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("connect() error!");
    }
    printf("[*] connected\n");
    double upload_bandwidth = 0;
    double download_bandwidth = 0;

    uint64_t upload_elapsed_time_sum = 0;
    uint64_t download_elapsed_time_sum = 0;

    for (int i = 0; i < 10 * 0x100; i++) {
        // upload
        printf("[*] upload %d\n", i);
        size_t start = get_ms();
        send(sock, message, BUF_SIZE, 0);
        size_t end = get_ms();
        upload_elapsed_time_sum += (end - start);

        // download
        printf("[*] download %d\n", i);
        start = get_ms();
        recv(sock, message, BUF_SIZE, 0);
        end = get_ms();
        download_elapsed_time_sum += (end - start);
    }
    printf("[*] upload elapsed time sum: %lu\n", upload_elapsed_time_sum);
    printf("[*] download elapsed time sum: %lu\n", download_elapsed_time_sum);
    
    upload_bandwidth = (double)(BUF_SIZE * 0x100ull * 10 * 1000) / (upload_elapsed_time_sum);
    download_bandwidth = (double)(BUF_SIZE * 0x100ull * 10 * 1000) / (download_elapsed_time_sum);

    printf("[*] upload bandwidth: %f\n", upload_bandwidth);
    printf("[*] download bandwidth: %f\n", download_bandwidth);

    close(sock);
    return 0;
}

