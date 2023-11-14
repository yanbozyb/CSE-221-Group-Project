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

    // Force file content to be written to disk
    if (fsync(fd) == -1) {
        perror("Error syncing file");
        close(fd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    free(buffer);
    close(fd);
}


int main() {
    const char* filename = "large_file.bin";
    createAndFillFile(filename);

    return 0;
}
