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
    int err;
    int icount;

    uiofd = open("/dev/uio0", O_RDONLY);
    if (uiofd < 0) {
        perror("uio open:");
        return errno;
    }

    /* Wait for next interrupt. */
    err = read(uiofd, &icount, 4);

    if (err != 4) {
        perror("uio read:");
    }
            
    return errno;
}

