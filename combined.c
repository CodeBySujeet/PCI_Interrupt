#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define NUM_MEASUREMENTS 10000
#define DELAY_BETWEEN_MEASUREMENTS_US 10000  // 10 milliseconds

struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main() {
    int uio_fd = open("/dev/uio0", O_RDWR);
    if (uio_fd < 0) {
        perror("Failed to open UIO device");
        return -1;
    }

    // Map control registers or memory regions if needed
    // volatile void* hw_regs = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, uio_fd, 0);

    struct timespec start_time, end_time, elapsed_time;
    double elapsed_time_in_ms;

    // Open file for writing results
    FILE* fp = fopen("timings.txt", "w");
    if (!fp) {
        perror("Failed to open file for writing");
        close(uio_fd);
        return -1;
    }

    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        // PCI Write Operation
        // *(volatile uint32_t*)(hw_regs + WRITE_OFFSET) = data; // Example write

        // Simulate a realistic delay for external processing, if necessary
        usleep(100); // Simulating external delay for response

        // PCI Read Operation
        // uint32_t read_data = *(volatile uint32_t*)(hw_regs + READ_OFFSET); // Example read

        clock_gettime(CLOCK_MONOTONIC, &end_time);
        elapsed_time = diff(start_time, end_time);

        elapsed_time_in_ms = (elapsed_time.tv_sec * 1000.0) + (elapsed_time.tv_nsec / 1000000.0);
        fprintf(fp, "%f\n", elapsed_time_in_ms);

        usleep(DELAY_BETWEEN_MEASUREMENTS_US);
    }

    fclose(fp);
    // Unmap and close UIO device
    // munmap((void*)hw_regs, map_size);
    close(uio_fd);

    return 0;
}
