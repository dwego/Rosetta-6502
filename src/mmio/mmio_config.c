#include "mmio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

MMIODevice mmio_devices[64];
int mmio_device_count = 0;

// Forward declaration of handlers implemented in default_handlers.c
extern Byte get_key(Word addr);
extern void print_char(Word addr, Byte data);
extern void vram_write(Word addr, Byte data);

extern Byte mmio_read_default(Word addr);
extern void mmio_write_default(Word addr, Byte data);

static mmio_read_t resolve_read(const char *name) {
    if (strcmp(name, "get_key") == 0) return get_key;
    return mmio_read_default;
}

static mmio_write_t resolve_write(const char *name) {
    if (strcmp(name, "print_char") == 0) return print_char;
    if (strcmp(name, "vram_write") == 0) return vram_write;
    return mmio_write_default;
}

MMIODevice *mmio_find_device(Word addr) {
    for (int i = 0; i < mmio_device_count; i++)
        if (addr >= mmio_devices[i].start &&
            addr <= mmio_devices[i].end)
            return &mmio_devices[i];
    return NULL;
}

void mmio_load_config(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("[MMIO] Config file not found: %s\n", filename);
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), f)) {

        if (line[0] == '#' || line[0] == '\n')
            continue;

        MMIODevice dev = {0};

        char read_handler[32] = {0};
        char write_handler[32] = {0};

        sscanf(
            line,
            "%31s %hx %hx read=%31s write=%31s",
            dev.name,
            &dev.start,
            &dev.end,
            read_handler,
            write_handler
        );

        if (strlen(read_handler) > 0 && strcmp(read_handler, "0") != 0)
            dev.read = resolve_read(read_handler);

        if (strlen(write_handler) > 0 && strcmp(write_handler, "0") != 0)
            dev.write = resolve_write(write_handler);

        mmio_devices[mmio_device_count++] = dev;

        printf("[MMIO] Loaded: %-10s  %04X-%04X\n",
               dev.name, dev.start, dev.end);
    }

    fclose(f);
}
