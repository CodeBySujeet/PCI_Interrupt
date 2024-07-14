#! /bin/bash

#gcc -o pci_interrupt pci_interrupt.c
#gcc -o pci_write_send pci_write_send.c
#gcc -o pci_receive_int pci_receive_int.c

g++ -o pci_write_send pci_write_send.c
g++ -o pci_receive_int pci_receive_int.c

g++ -o combined_luca combined_luca.c