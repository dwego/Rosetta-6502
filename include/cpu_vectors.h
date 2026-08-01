#ifndef CPU_VECTORS_H
#define CPU_VECTORS_H

/*
   MOS 6502 Processor Vectors

   The final six bytes of the 6502 address space contain the NMI, reset, and
   IRQ/BRK vectors.

   Each vector contains a 16-bit little-endian handler address.
*/
#define NMI_VECTOR 0xFFFA
#define RESET_VECTOR 0xFFFC
#define IRQ_VECTOR 0xFFFE

#endif /* CPU_VECTORS_H */