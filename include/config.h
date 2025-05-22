#ifndef CONFIG_H
#define CONFIG_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <stdint.h>
#include <stdint.h>
#include <time.h>

extern FILE *log_file;

void open_log(const char *filename);
void close_log(void);

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;
typedef uint64_t QWord;
typedef int8_t SignedByte;

static inline Byte get_bit(Byte byte, int position) {
    return (byte >> position) & 1;
}

#endif // CONFIG_H
