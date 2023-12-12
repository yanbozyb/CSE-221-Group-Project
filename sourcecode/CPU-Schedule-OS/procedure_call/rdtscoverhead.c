#include <stdio.h>
#include <stdint.h>
#include <sched.h>

static inline uint64_t __attribute__((__always_inline__)) rdtsc(void) {
	uint64_t cycles_lo, cycles_hi;
	
	asm volatile("rdtscp\n" :
		"=a" (cycles_lo), "=d" (cycles_hi) ::
		"%rcx");

	return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

int main() {
    uint64_t total_cycles = 0;
    for (int i = 0; i < 0x10000; i++) {
        uint64_t start = rdtsc();
        uint64_t end = rdtsc();
        total_cycles += end - start;
    }
    printf("rdtsc takes %f cycles\n", (double)total_cycles / 0x10000);
}
