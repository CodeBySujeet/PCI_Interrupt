import os
import mmap

uiofd = os.open("/dev/uio0", os.O_RDONLY)
resourcefd = os.open("/sys/class/uio/uio0/device/resource0", os.O_RDWR | os.O_SYNC)

memspace = mmap.mmap(resourcefd, 0x20000, mmap.MAP_SHARED, mmap.PROT_READ | mmap.PROT_WRITE)
icount = 0

while True:
    # Print out a message, for debugging.
    if icount == 0:
        print("Started uio test driver.")
    else:
        print("Interrupts:", icount)

    # Wait for next interrupt.
    icount = os.read(uiofd, 4)

    # Send message back to FPGA
    memspace[0x18] = 0x18 
    memspace.flush()

    if len(icount) != 4:
        print("uio read:", os.strerror(len(icount)))
        break

os.close(uiofd)
os.close(resourcefd)
