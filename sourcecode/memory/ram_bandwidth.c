#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 1 * (1 << 30) // 1GB

double measureReadBandwidth(volatile int* data, size_t size) {
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        volatile int sink = data[i]; // Just read the value to 'sink'
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return MEMORY_SIZE / time_taken / 1024 / 1024 / 1024;
}

double measureReadBandwidthAsm(volatile int* data, size_t size) {
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        int dummy;
        __asm__ volatile ("movl (%1), %0"
                          : "=r" (dummy)
                          : "r" (data + i)
                          : // No clobbered registers
                         );
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return MEMORY_SIZE / time_taken / 1024 / 1024 / 1024;
}

double measureWriteBandwidth(volatile int* data, size_t size) {
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        data[i] = i; // Simple write operation
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return MEMORY_SIZE / time_taken / 1024 / 1024 / 1024;
}

double measureWriteBandwidthAsm(volatile int* data, size_t size) {
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        int value = i; // The value to be written to memory
        __asm__ volatile ("movl %1, (%0)"
                          : // No output
                          : "r" (data + i), "r" (value)
                          : "memory" // Tells the compiler that memory is modified
                         );
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return MEMORY_SIZE / time_taken / 1024 / 1024 / 1024;
}

int main() {
    double readBandwidth, writeBandwidth;
    volatile int* data = (volatile int*)malloc(MEMORY_SIZE);
    if (data == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    readBandwidth = measureReadBandwidth(data, MEMORY_SIZE / sizeof(int));
    printf("Read Bandwidth: %f GB/sec\n", readBandwidth);

    readBandwidth = measureReadBandwidthAsm(data, MEMORY_SIZE / sizeof(int));
    printf("Read Bandwidth (ASM): %f GB/sec\n", readBandwidth);

    writeBandwidth = measureWriteBandwidth(data, MEMORY_SIZE / sizeof(int));
    printf("Write Bandwidth: %f GB/sec\n", writeBandwidth);

    writeBandwidth = measureWriteBandwidthAsm(data, MEMORY_SIZE / sizeof(int));
    printf("Write Bandwidth (ASM): %f GB/sec\n", writeBandwidth);
    free((int*)data);
    return 0;
}

