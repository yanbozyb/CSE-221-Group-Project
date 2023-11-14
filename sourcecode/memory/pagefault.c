#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define FILE_SIZE (1 << 30) // 1 GB
#define PAGE_SIZE 4096 // Assuming 4KB page size

void createAndFillFile(const char* filename) {
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Allocate and initialize a buffer to write to the file
    char* buffer = (char*)malloc(PAGE_SIZE);
    if (buffer == NULL) {
        perror("Error allocating buffer");
        close(fd);
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, PAGE_SIZE);


    // Write the buffer to the file multiple times to fill it
    for (size_t i = 0; i < FILE_SIZE; i += PAGE_SIZE) {
	for (int i = 0; i < PAGE_SIZE; i++) {
            buffer[i] = rand() % 256; // Random byte
    	}
        if (write(fd, buffer, PAGE_SIZE) != PAGE_SIZE) {
            perror("Error writing to file");
            close(fd);
            free(buffer);
            exit(EXIT_FAILURE);
        }
    }

    free(buffer);
    close(fd);
}

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

    volatile char sink; // Prevent optimization
    clock_t start = clock();

    for (size_t i = 0; i < FILE_SIZE; i += PAGE_SIZE) {
        sink = data[i]; // Access each page to cause a page fault
    }

    clock_t end = clock();
    munmap(data, FILE_SIZE);
    close(fd);

    return (double)(end - start) / CLOCKS_PER_SEC / (FILE_SIZE / PAGE_SIZE);
}

double measurePageFaultTimeRandom(const char* filename) {
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

    clock_t start = clock();

    volatile char sink; // Prevent optimization
    for (size_t i = 0; i < FILE_SIZE; i += PAGE_SIZE) {
        size_t index = (rand() % (FILE_SIZE / PAGE_SIZE)) * PAGE_SIZE; // Random page
        sink = data[index];
    }

    clock_t end = clock();
    munmap(data, FILE_SIZE);
    close(fd);

    return (double)(end - start) / CLOCKS_PER_SEC / (FILE_SIZE / PAGE_SIZE);
}

int main() {
    const char* filename = "large_file.bin";
    //createAndFillFile(filename);
    double avgPageFaultTime = measurePageFaultTimeRandom(filename);
    printf("Average Page Fault Service Time: %f ms\n", avgPageFaultTime * 1000);

    return 0;
}
