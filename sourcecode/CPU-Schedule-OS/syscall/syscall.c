#include <stdio.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static inline void __attribute__((__always_inline__)) time_syscall(void) {
    struct timespec ts;
    syscall(__NR_clock_gettime, CLOCK_MONOTONIC, &ts);
}

static inline void __attribute__((__always_inline__)) time_libc(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
}

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
    uint64_t cycles_lo, cycles_hi;
    asm volatile("rdtscp\n" : "=a"(cycles_lo), "=d"(cycles_hi)::
                                                   "%rcx");
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

int main() {
    uint64_t syscall_total = 0;
    uint64_t start, end;
    for (int i = 0; i < 0x10000; ++i) {
        start = rdtsc();
        time_syscall();
        end = rdtsc();
        syscall_total += end - start;
    }
    printf("[*] syscall takes %f cycles\n", (double)(syscall_total) / 0x10000);

    uint64_t libc_total = 0;
    for (int i = 0; i < 0x10000; ++i) {
        start = rdtsc();
        time_libc();
        end = rdtsc();
        libc_total += end - start;
    }
    printf("[*] libc takes %f cycles\n", (double)(libc_total) / 0x10000);
}