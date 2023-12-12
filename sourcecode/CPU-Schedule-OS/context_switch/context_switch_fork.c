#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_ITERATIONS 0x10000

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
    uint64_t cycles_lo, cycles_hi;
    asm volatile("rdtscp\n" : "=a"(cycles_lo), "=d"(cycles_hi)::
                                                   "%rcx");
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

void process_func() {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sched_yield();
    }
}

int main() {
    if (getuid() != 0) {
        fprintf(stderr, "You must run this program as root!\n");
        exit(1);
    }
    struct sched_param param = {
        .sched_priority = 1
    };

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler failed");
        exit(1);
    }

    pthread_t thread;
    int pid = fork();
    if (pid == 0) {
        process_func();
        exit(0);
    } else if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    uint64_t start = rdtsc();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sched_yield();
    }
    uint64_t end = rdtsc();
    
    printf("[*] Start: %lu\n", start);
    printf("[*] End: %lu\n", end);
    // result is divided by 2 because we are measuring the time for 2 context switches
    printf("[*] Context switch time: %f\n", ((double)(end - start)) / NUM_ITERATIONS / 2);

    return 0;
}
