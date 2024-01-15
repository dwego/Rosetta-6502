#ifndef CONFIG_H
#define CONFIG_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <stdint.h>
#include <stdint.h>

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;
typedef uint64_t QWord;

Byte get_bit(unsigned char byte, int position) {
    return (byte >> position) & 1;
}

#endif // CONFIG_H