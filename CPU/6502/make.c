#include "config.h"
#include "mem6502.h"
#include "cpu6502.h"
#include "instructions.h"
#include "lda.h"
#include "jsr.h"
#include "stx.h"
#include "sta.h"
#include "ldx.h"
#include "ldy.h"

void
execute(Word *Cycles, MEM6502 *memory,
        CPU6502 *cpu)
{
    Byte Ins = FetchByte(Cycles, memory, cpu);
    switch ( Ins )
    {
        case INS_LDA_IM:
        {
            LDA_IM(Cycles, memory, cpu);

            break;
        }
        case INS_LDA_ZP:
        {
            LDA_ZP(Cycles, memory, cpu);

            break;
        }
        case INS_LDA_ZPX:
        {
            LDA_ZPX(Cycles, memory, cpu);

            break;
        }
        case INS_LDA_ABS:
        {
            LDA_ABS(Cycles, memory, cpu);

            break;
        }
        case INS_LDA_ABSX:
        {
            LDA_ABSX(Cycles, memory, cpu);

            break;
        }
        case INS_LDA_ABSY:
        {
            LDA_ABSY(Cycles, memory, cpu);

            break;
        }
        case INS_LDX_IM:
        {
            LDX_IM(Cycles, memory, cpu);

            break;
        }
        case INS_LDX_ZP:
        {
            LDX_ZP(Cycles, memory, cpu);

            break;
        }
        case INS_LDX_ZPY:
        {
            LDX_ZPY(Cycles, memory, cpu);

            break;
        }
        case INS_LDX_ABS:
        {
            LDX_ABS(Cycles, memory, cpu);

            break;
        }
        case INS_LDX_ABSY:
        {
            LDX_ABSY(Cycles, memory, cpu);

            break;
        }
        case INS_LDY_ZP:
        {
            LDY_ZP(Cycles, memory, cpu);

            break;
        }
        case INS_LDY_ZPX:
        {
            LDY_ZPX(Cycles, memory, cpu);

            break;
        }
        case INS_LDY_ABS:
        {
            LDY_ABS(Cycles, memory, cpu);

            break;
        }
        case INS_LDY_ABSX:
        {
            LDY_ABSX(Cycles, memory, cpu);

            break;
        }
        case INS_STA_ZP:
        {
            LDA_IM(Cycles, memory, cpu);

            break;
        }
        case INS_STA_ZPX:
        {
            LDA_ZP(Cycles, memory, cpu);

            break;
        }
        case INS_STA_ABS:
        {
            LDA_ZPX(Cycles, memory, cpu);

            break;
        }
        case INS_STA_ABSX:
        {
            LDA_ABS(Cycles, memory, cpu);

            break;
        }
        case INS_STA_ABSY:
        {
            LDA_ABSX(Cycles, memory, cpu);

            break;
        }
        case INS_JSR:
        {
            JSR(Cycles, memory, cpu);

            break;
        }
        case INS_RTS:
        {
            RTS(Cycles, memory, cpu);

            break;
        }
        default:
            printf("Instruction not handled %d\n", Ins);
            (*Cycles) = 0;
            break;
    }

}

int
main(void)
{
    CPU6502 cpu;
    MEM6502 mem;
    Byte test;
    Word Cycles = 20;

    resetCPU(0xFFFC, &cpu, &mem);
    // start - inline a little program
    mem.Data[0xFFFC] = INS_LDA_IM;
    mem.Data[0xFFFD] = 0x10 ;
    mem.Data[0xFFFE] = INS_STA_ZP;
    mem.Data[0xFFFF] = 0x42;

    // end - inline a little program
    execute(&Cycles, &mem, &cpu);

    if (Cycles == 0) {
        goto end;
    }

    clock:
    execute(&Cycles, &mem, &cpu);
    if (Cycles != 0) {
        goto clock;
    }


    end:
    test = mem.Data[0x0042];
    printf("stored value in: [0x0042] is: %u\n", test);
    freeMem6502(&mem);

    return 0;
}