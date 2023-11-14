#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define FILE_SIZE ((uint64_t)1 << 30) * 10
#define PAGE_SIZE 4096 // Assuming 4KB page size

double measurePageFaultTime(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char* data = (char*)mmap(NULL, FILE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    uint64_t num_pages = FILE_SIZE / PAGE_SIZE;
    size_t* indices = malloc(num_pages * sizeof(size_t));
    for (size_t i = 0; i < num_pages; ++i) {
        indices[i] = i;
    }
    // Shuffle indices to access pages randomly
    for (size_t i = num_pages - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        size_t temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    clock_t start = clock();
    volatile char sink;
    for (size_t i = 0; i < num_pages; ++i) {
        sink = data[indices[i] * PAGE_SIZE];
    }
    clock_t end = clock();

    free(indices);
    munmap(data, FILE_SIZE);
    close(fd);

    return (double)(end - start) / CLOCKS_PER_SEC / num_pages;
}

int main() {
    const char* filename = "large_file.bin";
    double avgPageFaultTime = measurePageFaultTime(filename);
    printf("Average Page Fault Service Time: %f ms\n", avgPageFaultTime * 1000);

    return 0;
}
