#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <signal.h>
// #include "inline_hooker.h"
// #include "utils.h"

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void)
{
    uint64_t cycles_lo, cycles_hi;
    asm volatile("rdtscp\n" : "=a"(cycles_lo), "=d"(cycles_hi)::
                                                   "%rcx");
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

int main() {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    if (setpriority(PRIO_PROCESS, 0, -20)) {
        printf("[*] Please try to run as root\n");
        perror("setpriority");
        exit(1);
    }
    static size_t tot = 0;
    static size_t start = 0, end = 0;
    const int flags = CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID | SIGCHLD;
    uint64_t ctid = 0;
    for (int i = 0; i < 0x10000; i++) {   
        start = rdtsc();
        int pid = syscall(__NR_clone, flags, NULL, NULL, NULL, &ctid);
        if (pid == 0) {
            exit(0);
        }
        end = rdtsc();
        tot += end - start;
        waitpid(pid, NULL, 0);
    }
    printf("avg: %f\n", (double)tot / 0x10000);

    return 0;
}
