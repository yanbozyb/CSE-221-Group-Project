#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 0x10000

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
    uint64_t cycles_lo, cycles_hi;
    asm volatile("rdtscp\n" : "=a"(cycles_lo), "=d"(cycles_hi)::
                                                   "%rcx");
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

uint64_t total = 0;

int test(const char **argv) {
    int sock;
    struct sockaddr_in serv_addr;

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
    
    uint64_t start = rdtsc();
    connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    close(sock);
    shutdown(sock, SHUT_RDWR);
    uint64_t end = rdtsc();
    total += end - start;
    printf("[*] cycles: %lu\n", end - start);
    return 0;
}

int main(int argc, const char **argv) {
    for(int i = 0; i < 0x100; i++) {
        test(argv);
    }
    printf("[*] average cycles: %lu\n", total / 0x100);
}

