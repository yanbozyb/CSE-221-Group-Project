#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define BLOCK_SIZE 4096
#define MAX_FILE_SIZE 1073741824 // 1 GB for example
				 //
// Function to calculate the difference between two timespecs
double timespecDiff(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1e9 + end->tv_nsec - start->tv_nsec;
}

// Sequential read function
double measureSequentialRead(int fd, size_t fileSize) {
    char *buffer = (char *)aligned_alloc(BLOCK_SIZE, BLOCK_SIZE);
    struct timespec start, end;
    double totalTime = 0;
    int numBlocks = fileSize / BLOCK_SIZE;

    for (int i = 0; i < numBlocks; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        pread(fd, buffer, BLOCK_SIZE, BLOCK_SIZE * i);
        clock_gettime(CLOCK_REALTIME, &end);

        totalTime += timespecDiff(&start, &end);
    }

    free(buffer);

    double avg_time = totalTime / numBlocks;
    return avg_time;
}

// Random read function
double measureRandomRead(int fd, size_t fileSize) {
    char *buffer = (char *)aligned_alloc(BLOCK_SIZE, BLOCK_SIZE);
    struct timespec start, end;
    double totalTime = 0;
    int numBlocks = fileSize / BLOCK_SIZE;

    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < numBlocks; i++) {
        int blockNum = rand() % numBlocks;

        clock_gettime(CLOCK_REALTIME, &start);
        pread(fd, buffer, BLOCK_SIZE, BLOCK_SIZE * blockNum);
        clock_gettime(CLOCK_REALTIME, &end);

        totalTime += timespecDiff(&start, &end);
    }

    free(buffer);

    double avg_time = totalTime / numBlocks;
    return avg_time;	
}

int main(int argc, char **argv) {
    int fd = open("testfile", O_RDONLY | O_DIRECT);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("random writes:\n");
    for (long file_size = BLOCK_SIZE; file_size <= MAX_FILE_SIZE; file_size *= 2) {

    	double time = measureRandomRead(fd, file_size);
        printf("File size: %ld KB, Read time: %.3f ms\n", file_size / 1024, time / 1000 / 1000);

    }

    printf("sequential writes:\n");
    for (long file_size = BLOCK_SIZE; file_size <= MAX_FILE_SIZE; file_size *= 2) {

        double time = measureSequentialRead(fd, file_size);
        printf("File size: %ld KB, Read time: %.3f ms\n", file_size / 1024, time / 1000 / 1000);

    }

    close(fd);
    return 0;
}

