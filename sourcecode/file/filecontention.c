#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>

#define BLOCK_SIZE 4096   
#define NUM_BLOCKS 1024

double timespecDiff(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1e9 + end->tv_nsec - start->tv_nsec;
}

void readRandomBlocksDirectIO(const char* filename) {
    int fd = open(filename, O_RDONLY | O_DIRECT);
    if (fd == -1) {
        fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    off_t fileSize;
    if ((fileSize = lseek(fd, 0, SEEK_END)) == -1) {
        fprintf(stderr, "Error seeking file %s: %s\n", filename, strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    void* buffer;
    if (posix_memalign(&buffer, BLOCK_SIZE, BLOCK_SIZE)) {
        fprintf(stderr, "Error in posix_memalign: %s\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    //struct timeval start, end;
    struct timespec start, end;
    //long totalMicroseconds = 0;
    double totalTime = 0;
    srand((unsigned int)time(NULL) ^ (getpid()));

    for (int i = 0; i < NUM_BLOCKS; i++) {
        off_t offset = (rand() % (fileSize / BLOCK_SIZE)) * BLOCK_SIZE;

        //gettimeofday(&start, NULL);
	clock_gettime(CLOCK_REALTIME, &start);
        if (pread(fd, buffer, BLOCK_SIZE, offset) == -1) {
            fprintf(stderr, "Error reading file %s: %s\n", filename, strerror(errno));
            free(buffer);
            close(fd);
            exit(EXIT_FAILURE);
        }
        //gettimeofday(&end, NULL);
	clock_gettime(CLOCK_REALTIME, &end);
	totalTime += timespecDiff(&start, &end);
        //totalMicroseconds += (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    }
    double latency = totalTime / NUM_BLOCKS / 1000 / 1000;
    printf("Average time per block: %.3f ms\n", latency);
    //printf("Average time per block: %ld ms\n", totalMicroseconds / NUM_BLOCKS);

    free(buffer);
    close(fd);
}

int main(int argc, char *argv[]) {
    int numProcesses = 16;
    char filename[20];

    for (int num = 1; num <= numProcesses; num++) {
	printf("num of process: %d\n", num);
	int shouldwait = num;
    	for (int i = 0; i < num; i++) {
        	pid_t pid = fork();
        	if (pid == 0) {
	    		sprintf(filename, "testfile%d", i);
            		readRandomBlocksDirectIO(filename);
            		exit(EXIT_SUCCESS);
        	} else if (pid < 0) {
            		fprintf(stderr, "Fork failed\n");
            		exit(EXIT_FAILURE);
        	}
    	}
    
    	while (shouldwait > 0) {
        	wait(NULL);
        	shouldwait--;
    	}
    }

    return 0;
}

