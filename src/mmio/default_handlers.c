#include "mmio.h"
#include <stdio.h>

Byte mmio_read_default(Word addr) {
    printf("[MMIO READ] %04X -> default\n", addr);
    return 0;
}

void mmio_write_default(Word addr, Byte data) {
    printf("[MMIO WRITE] %04X <= %02X (default)\n", addr, data);
}

/* --- Example handlers --- */

int mmio_exit_requested = 0;
Byte mmio_exit_code = 0;

void mmio_exit(Word addr, Byte data) {
    (void)addr;
    mmio_exit_code = data;
    mmio_exit_requested = 1;
    printf("[EXIT] requested (code=%02X)\n", data);
    fflush(stdout);
}


Byte get_key() {
    printf("[MMIO KEYBD] waiting for key...\n");
    int c = getchar();
    printf("[MMIO KEYBD] got '%c' (%02X)\n", c, (unsigned char)c);
    return (Byte)c;
}


void print_char(Word addr, Byte data) {
    printf("[PRINTCHAR %02X '%c']\n", addr, data);
    fflush(stdout);
}

void vram_write(Word addr, Byte data) {
    printf("[VRAM] %04X <= %02X\n", addr, data);
}
