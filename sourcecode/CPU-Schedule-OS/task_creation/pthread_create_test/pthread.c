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
#include <sys/mman.h>
#include <dlfcn.h>
// #include "inline_hooker.h"

uint64_t total_cycles = 0;
uint64_t *g_cycles_start_ptr = 0;

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
    uint64_t cycles_lo, cycles_hi;
    asm volatile("rdtscp\n" : "=a"(cycles_lo), "=d"(cycles_hi)::
                                                   "%rcx");
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

void init_global() {
   void *l = dlsym(RTLD_DEFAULT, "g_get_cycles_start");
   g_cycles_start_ptr = (uint64_t *)l;
}


void thread_func() {
    extern uint64_t g_cycles_start;
    total_cycles += (rdtsc() - g_cycles_start);
}

int main() {
    if (getuid() != 0) {
        printf("[-] run as root\n");
        return 1;
    }
    // init_global();
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    printf("%d\n", setpriority(PRIO_PROCESS, 0, -20));

    // printf("installing hook\n");
    // install_hook(0x7ffff7c3f436, (uintptr_t)jump_target);

    for(int i = 0; i < 0x10000; i++) {	
        pthread_t thread;
        pthread_create(&thread, 0, (void *(*)(void *))thread_func, NULL);
        pthread_join(thread, NULL);
    }
    printf("avg %f\n", (double)total_cycles / 0x10000);
    return 0;
}

