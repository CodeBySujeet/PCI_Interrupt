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
    int uiofd;
    int configfd;
    int err;
    int err2;
    int i;
    unsigned icount;

    int resourcefd;
    volatile unsigned int *memspace;

    uiofd = open("/dev/uio0", O_RDONLY);
    if (uiofd < 0) {
        perror("uio open:");
        return errno;
    }

    resourcefd = open("/sys/class/uio/uio0/device/resource0", O_RDWR | O_SYNC);
    if (resourcefd < 0) {
        perror("resource open:");
        return errno;
    }
    memspace = mmap(NULL, 0x20000, PROT_READ | PROT_WRITE, MAP_SHARED, resourcefd, 0);

    /* file descriptor monitoring */
    fd_set rfds;
    struct timeval tv;
    FD_ZERO(&rfds);
    FD_SET(uiofd, &rfds);

    for(i = 0;; ++i) {
        FD_ZERO(&rfds);
        FD_SET(uiofd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        int ret_sel = select(uiofd+1, &rfds, NULL, NULL, &tv);

        if (ret_sel == -1) {
            perror("select:");
            break;
        } else if (ret_sel) {
            /* Wait for next interrupt. */
            err = read(uiofd, &icount, 4);

            /* Send message back to FPGA */
            memspace[0x18] = 0x18;
            msync((void *)(memspace + 0x18), 4, MS_SYNC|MS_INVALIDATE);

            if (err != 4) {
                perror("uio read:");
                break;
            }
            //fprintf(stderr, "Interrupts: %d\n", icount);
        }
    }
    return errno;
}

