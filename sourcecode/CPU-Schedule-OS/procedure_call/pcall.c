#include <stdio.h>
#include <stdint.h>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>

extern void foo0();
extern void foo1(size_t a);
extern void foo2(size_t a, size_t b);
extern void foo3(size_t a, size_t b, size_t c);
extern void foo4(size_t a, size_t b, size_t c, size_t d);
extern void foo5(size_t a, size_t b, size_t c, size_t d, size_t e);
extern void foo6(size_t a, size_t b, size_t c, size_t d, size_t e, size_t f);
extern void foo7(size_t a, size_t b, size_t c, size_t d, size_t e, size_t f, size_t g);

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
	uint64_t cycles_lo, cycles_hi;
	
	asm volatile("rdtscp\n" :
		"=a" (cycles_lo), "=d" (cycles_hi) ::
		"%rcx");

	return ((uint64_t)cycles_hi << 32) | cycles_lo;
}


int main() {
    // force out program run on the same core
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    foo0();
    foo1(1);
    foo2(1, 2);
    foo3(1, 2, 3);
    foo4(1, 2, 3, 4);
    foo5(1, 2, 3, 4, 5);
    foo6(1, 2, 3, 4, 5, 6);
    foo7(1, 2, 3, 4, 5, 6, 7);

    for(int k = 0; k < 0x1; ++k) {
        size_t tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo0();
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo0 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo1(1);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo1 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo2(1, 2);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo2 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo3(1, 2, 3);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo3 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo4(1, 2, 3, 4);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo4 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo5(1, 2, 3, 4, 5);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo5 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo6(1, 2, 3, 4, 5, 6);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo6 takes %f cycles\n", (double)(tot) / 0x10000);
        tot = 0;
        for (int i = 0; i < 0x10000; i++) {
            uint64_t start = rdtsc();
            foo7(1, 2, 3, 4, 5, 6, 7);
            uint64_t end = rdtsc();
            tot += end - start;
        }
        printf("foo7 takes %f cycles\n", (double)(tot) / 0x10000);
    }
    return 0;
}

#if 0
foo0 takes 480227226 cycles
foo0 takes 28.623773 cycles
foo1 takes 484087872 cycles
foo1 takes 28.853886 cycles
foo2 takes 477800796 cycles
foo2 takes 28.479147 cycles
foo3 takes 482802028 cycles
foo3 takes 28.777243 cycles
foo4 takes 483055082 cycles
foo4 takes 28.792327 cycles
foo5 takes 497502050 cycles
foo5 takes 29.653433 cycles
foo6 takes 494923066 cycles
foo6 takes 29.499714 cycles
foo7 takes 513892914 cycles
foo7 takes 30.630405 cycles
#endif
