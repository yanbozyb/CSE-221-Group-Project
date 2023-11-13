#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define OPERATION p = (char **)*p;
#define MIN_MEM_SIZE 512
#define MAX_MEM_SIZE 8 * 1024 * 16384
#define STRIP 256

static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (
        "rdtsc" : "=a" (lo), "=d" (hi)
    );
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    int i, j, tmp;
    size_t size, strip = STRIP;
    int *chain_list;
    size_t memsize = MIN_MEM_SIZE;

    const double cpu_freq = 2.9e9; // curren cpu frequency

    // allocate and access memory regions of increasing size to find the latency
    for (; memsize <= (MAX_MEM_SIZE); memsize *= 2) {
        // map memory to prevent it from being allocated in the swap
        char* segment = mmap(NULL, memsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (segment == MAP_FAILED) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        // allocate chain_list array
        size = memsize / strip;
        chain_list = malloc(size * sizeof(int));
        if (!chain_list) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // initialize chain_list with random values to simulate random access
        for (i = 0; i < size; i++)
            chain_list[i] = i;

        for (i = 0; i < size; i++) {
            j = i + rand() % (size - i);
            tmp = chain_list[i];
            chain_list[i] = chain_list[j];
            chain_list[j] = tmp;
        }

        // fill memory with pointer references to create a chain
        for (i = 0; i < size - 1; i++)
            *(char **)&segment[chain_list[i] * strip] = (char*)&segment[chain_list[i + 1] * strip];
        *(char **)&segment[chain_list[size - 1] * strip] = (char*)&segment[chain_list[0] * strip];

        register char **p = (char **)segment;

        // measure access time using rdtsc
        uint64_t start_cycles = rdtsc();
        tmp = size * 100;
        for (i = 0; i < tmp; i++) {
            OPERATION;
        }
        uint64_t end_cycles = rdtsc();

        // prevent potential optimization
        char **pp = p;
        (void)pp;

        // calculate the number of cycles and convert to time
        uint64_t cycles = end_cycles - start_cycles;
        double time_diff = cycles / cpu_freq; // seconds
        double latency = (time_diff / tmp) * 1e9; // convert to nanoseconds

        if (memsize >= 1024) {
                printf("buffer: %zu KB, cycles %llu, time %f s, latency %f ns\n",
                memsize / 1024, cycles, time_diff, latency);
        }

        munmap(segment, memsize);
        free(chain_list);
    }

    return 0;
}
