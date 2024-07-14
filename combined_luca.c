#include <x86intrin.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <time.h>
#include <fstream>
#include <iostream>

int main(int argc, const char** argv) {
    int uiofd;
    int err;
    int icount;
    int resourcefd;

    unsigned long long start, stop;


    uiofd = open("/dev/uio0", O_RDONLY);
    if (uiofd < 0) {
        perror("uio open:");
        return errno;
    }

    volatile unsigned int *memspace;
    resourcefd = open("/sys/class/uio/uio0/device/resource0", O_RDWR | O_SYNC);
    if (resourcefd < 0) {
        perror("resource open:");
        return errno;
    }
    memspace = (volatile unsigned int*) mmap(NULL, 0x20000, PROT_READ | PROT_WRITE, MAP_SHARED, resourcefd, 0);

    std::ofstream f("latencies.txt");

    int iterations;
    std::cout<<"No of iterations:";
    std::cin>>iterations;

    std::cout<<std::endl;

    int sleep_time;
    std::cout<<"Sleep time:";
    std::cin>>sleep_time;
    
    start = __rdtsc();
    usleep(1000000);
    stop = __rdtsc();
    double div=stop-start;


    for (int i = 0; i < iterations; i++) {
        start = __rdtsc();
        memspace[0x18] = 0x18;
        msync((void *)(memspace + 0x18), 4, MS_SYNC|MS_INVALIDATE);

        /* Wait for next interrupt. */
        err = read(uiofd, &icount, 4);
        stop = __rdtsc();

        if (err != 4) {
            perror("uio read:");
        }
        double rand= (stop-start);
        double time=(rand)/div;
        // std:: cout<<time;
        // std::cout<<std::endl;
        f << time << "\n";

        usleep(sleep_time);
    }

    // start = __rdtsc();
    // usleep(1000000);
    // stop = __rdtsc();

    // std::cout << stop-start << std::endl;
            
    return errno;
}

// have to record correctized time
// histogram no of iterations with standart deviation 
// 