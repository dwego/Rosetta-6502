#ifndef BRK_H
#define BRK_H

#include "config.h"
#include "cpu6502.h"
#include "mem6502.h"

void BRK(Word *Cycles, MEM6502 *mem, CPU6502 *cpu) {
    // Incrementa PC para o próximo endereço (2 bytes)
    cpu->PC += 2;
    (*Cycles)--;  

    // Empilha PC (high byte, depois low byte)
    PushPCToStack(Cycles, mem, cpu);

    // Prepara status para empilhamento: PS com bit B setado (bit 4)
    Byte status_with_B = cpu->PS | 0x10;

    // Empilha o status com o bit B setado
    PushByteToStack(Cycles, mem, status_with_B, cpu);

    // Set Interrupt Disable flag para bloquear interrupções futuras
    cpu->Flag.I = 1;
    cpu->PS |= (1 << 2); // bit I setado no PS

    // O bit B NÃO deve ficar setado na CPU, apenas no status empilhado

    // Lê vetor de interrupção (IRQ/BRK) em $FFFE/$FFFF
    Byte lo = mem->Data[0xFFFE];
    Byte hi = mem->Data[0xFFFF];
    cpu->PC = (hi << 8) | lo;
    (*Cycles) -= 2;
     spend_cycles(7);
}

#endif // BRK_H
