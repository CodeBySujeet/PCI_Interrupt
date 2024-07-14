#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/select.h>

int main()
{
    int resourcefd;

    volatile unsigned int *memspace;

    resourcefd = open("/sys/class/uio/uio0/device/resource0", O_RDWR | O_SYNC);
    if (resourcefd < 0) {
        perror("resource open:");
        return errno;
    }
    memspace = (volatile unsigned int*) mmap(NULL, 0x20000, PROT_READ | PROT_WRITE, MAP_SHARED, resourcefd, 0);

    memspace[0x18] = 0x18;
    msync((void *)(memspace + 0x18), 4, MS_SYNC|MS_INVALIDATE);
    return errno;
}

