#ifndef BUS_H
#define BUS_H

#include "config.h"

typedef struct
{
  Word address;
  Byte data;
  bool rw;
} Bus6502;

#endif // BUS_H
