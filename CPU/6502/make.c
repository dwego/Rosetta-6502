
#include "../include/config.h"

void execute(Word *Cycles, MEM6502 *memory, CPU6502 *cpu) {
    while (*Cycles > 0) {
        Byte Ins = FetchByte(Cycles, memory, cpu);
        switch ( Ins ) {
            case INS_LDA_IM: {
                LDA_IM(Cycles, memory, cpu);
                break;
            }
            case INS_LDA_ZP: {
                LDA_ZP(Cycles, memory, cpu);
                break;
            }
            case INS_LDA_ZPX: {
                LDA_ZPX(Cycles, memory, cpu);
                break;
            }
            case INS_LDA_ABS: {
                LDA_ABS(Cycles, memory, cpu);
                break;
            }
            case INS_LDA_ABSX: {
                LDA_ABSX(Cycles, memory, cpu);
                break;
            }
            case INS_LDA_ABSY: {
                LDA_ABSY(Cycles, memory, cpu);
                break;
            }
            case INS_JSR: {
                JSR(Cycles, memory, cpu);
                break;
            }
            case INS_RTS: {
                RTS(Cycles, memory, cpu);
                break;
            }
            default:
                printf("Instruction not handled %d", Ins);
                (*Cycles) = 0;
                break;
        }
    }

}