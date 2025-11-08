#ifndef ACCESS_TYPE_H
#define ACCESS_TYPE_H

typedef enum {
    ACCESS_NONE   = 0,
    ACCESS_RAM    = 1 << 0,
    ACCESS_ROM    = 1 << 1,
    ACCESS_MMIO   = 1 << 2
} AccessType;

#endif
