#ifndef CONFIG_H
#define CONFIG_H

#if defined(__APPLE__)
#include <err.h>
#define error(status, errnum, fmt, ...) errx(status, fmt, ##__VA_ARGS__)
#else
#include <error.h>
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_SIZE 256
#define MAX_LINES 1000

extern FILE *log_file;

void open_log (const char *filename);
void close_log (void);

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;
typedef uint64_t QWord;
typedef int8_t SignedByte;

static inline Byte
get_bit (Byte byte, int position)
{
  return (byte >> position) & 1;
}

#endif // CONFIG_H
