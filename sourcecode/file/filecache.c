#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILE_SIZE 1073741824 // 1 GB for example

double measure_read_time(const char *filename, long file_size) {
    char *buffer = malloc(file_size);
    if (buffer == NULL) {
        perror("Malloc failed");
        exit(1);
    }

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File open failed");
        free(buffer);
        exit(1);
    }

    // Read file and measure time
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    fread(buffer, 1, file_size, file);
    clock_gettime(CLOCK_REALTIME, &end);

    fclose(file);
    free(buffer);

    // Calculate time in milliseconds
    double time_taken = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    return time_taken;
}

int main() {
    for (long file_size = 1024; file_size <= MAX_FILE_SIZE; file_size *= 2) {

        double time = measure_read_time("testfile", file_size);
        printf("File size: %ld KB, Read time: %.3f ms\n", file_size / 1024, time);

    }

    return 0;
}

