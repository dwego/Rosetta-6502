#ifndef MMIO_H
#define MMIO_H

#include "config.h"

extern int mmio_exit_requested;
extern Byte mmio_exit_code;

typedef Byte (*mmio_read_t)(Word addr);
typedef void (*mmio_write_t)(Word addr, Byte data);

typedef struct {
    char name[32];
    Word start;
    Word end;
    mmio_read_t read;
    mmio_write_t write;
} MMIODevice;

extern MMIODevice mmio_devices[64];
extern int mmio_device_count;

void mmio_load_config(const char *filename);
MMIODevice *mmio_find_device(Word addr);

#endif
