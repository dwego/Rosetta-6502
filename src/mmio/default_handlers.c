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

Byte get_key(Word addr) {
    int c = getchar();
    return (Byte)c;
}

void print_char(Word addr, Byte data) {
    putchar(data);
    fflush(stdout);
}

void vram_write(Word addr, Byte data) {
    printf("[VRAM] %04X <= %02X\n", addr, data);
}
