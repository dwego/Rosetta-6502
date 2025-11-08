#include "ADC/adc.h"
#include "AND/and.h"
#include "ASL/asl.h"
#include "BCC/bcc.h"
#include "BCS/bcs.h"
#include "BEQ/beq.h"
#include "BIT/bit.h"
#include "BMI/bmi.h"
#include "BNE/bne.h"
#include "BPL/bpl.h"
#include "BVC/bvc.h"
#include "BVS/bvs.h"
#include "CLC/clc.h"
#include "CLD/cld.h"
#include "CLI/cli.h"
#include "CLV/clv.h"
#include "CMP/cmp.h"
#include "CPX/cpx.h"
#include "CPY/cpy.h"
#include "DEC/dec.h"
#include "DEX/dex.h"
#include "DEY/dey.h"
#include "EOR/eor.h"
#include "INC/inc.h"
#include "INX/inx.h"
#include "INY/iny.h"
#include "JMP/jmp.h"
#include "JSR/jsr.h"
#include "LDA/lda.h"
#include "LDX/ldx.h"
#include "LDY/ldy.h"
#include "LSR/lsr.h"
#include "NOP/nop.h"
#include "ORA/ora.h"


#include "PHA/pha.h"
#include "PHP/php.h"
#include "PLA/pla.h"
#include "PLP/plp.h"
#include "ROL/rol.h"
#include "ROR/ror.h"
#include "RTS/rts.h"

#include "SBC/sbc.h"
#include "SEC/sec.h"

#include "SEI/sei.h"
#include "STA/sta.h"
#include "STX/stx.h"
#include "STY/sty.h"
#include "TAX/tax.h"
#include "TAY/tay.h"
#include "TSX/tsx.h"
#include "TXA/txa.h"
#include "TXS/txs.h"
#include "TYA/tya.h"
#include "BRK/brk.h"
#include "EOR/eor.h"
#include "RTI/rti.h"

/* 
   This enumeration defines opcodes for various instructions supported by the MOS Technology 6502 processor.
   Each opcode represents a specific instruction that the processor can execute.

   The instructions are categorized based on their functionality, such as data loading (LDA, LDX, LDY), 
   data storing (STA, STX, STY), logical operations (AND, ORA, EOR, BIT), transfer operations (TAX, TAY, TXA, TYA),
   increments/decrements (INX, INY, DEY, DEX, DEX, INC), branches (BEQ, BNE, BCS, BCC, BMI, BPL, BVC, BVS),
   status flag changes (CLC, SEC, CLD, SED, CLI, SEI, CLV), arithmetic operations (ADC, SBC), and more.

   The enum values are hexadecimal representations of the corresponding opcodes for better readability.
   For more information about the instructions, refer to Instructions.MD
*/ 

typedef enum {
    
    //LDA
    INS_LDA_IM = 0xA9, // done
    INS_LDA_ZP = 0xA5, // done
    INS_LDA_ZPX = 0xB5, // done
    INS_LDA_ABS = 0xAD, // done
    INS_LDA_ABSX = 0xBD, // done
    INS_LDA_ABSY = 0xB9, // done
    INS_LDA_INDX = 0xA1, // done
    INS_LDA_INDY = 0xB1, // done

    //LDX
    INS_LDX_IM = 0xA2, // done
    INS_LDX_ZP = 0xA6, // done
    INS_LDX_ZPY = 0xB6, // done
    INS_LDX_ABS = 0xAE, // done
    INS_LDX_ABSY = 0xBE, // done

    //LDY
    INS_LDY_IM = 0xA0, // done
    INS_LDY_ZP = 0xA4, // done
    INS_LDY_ZPX = 0xB4, // done
    INS_LDY_ABS = 0xAC, // done
    INS_LDY_ABSX = 0xBC, // done

    //STA
    INS_STA_ZP = 0x85, // done
    INS_STA_ZPX = 0x95, // done
    INS_STA_ABS = 0x8D, // done
    INS_STA_ABSX = 0x9D, // done
    INS_STA_ABSY = 0x99, // done
    INS_STA_INDX = 0x81, // done
    INS_STA_INDY = 0x91, // done

    //STX
    INS_STX_ZP = 0x86, // done
    INS_STX_ZPY = 0x96, // done
    INS_STX_ABS = 0x8E, // done

    //STY
    INS_STY_ZP = 0x84, // done
    INS_STY_ZPX = 0x94, // done
    INS_STY_ABS = 0x8C, // done

    INS_TSX = 0xBA, // done
    INS_TXS = 0x9A, // done
    INS_PHA = 0x48, // done
    INS_PLA = 0x68, // done
    INS_PHP = 0x08, // done
    INS_PLP = 0x28, // done

    INS_JMP_ABS = 0x4C, // done
    INS_JMP_IND = 0x6C, // done
    INS_JSR = 0x20, // done
    INS_RTS = 0x60, // done

    //Logical Ops

    //AND

    INS_AND_IM = 0x29, // done
    INS_AND_ZP = 0x25, // done
    INS_AND_ZPX = 0x35, // done
    INS_AND_ABS = 0x2D, // done
    INS_AND_ABSX = 0x3D, // done
    INS_AND_ABSY = 0x39, // done
    INS_AND_INDX = 0x21, // done
    INS_AND_INDY = 0x31, // done

    //ORA

    INS_ORA_IM = 0x09, // done
    INS_ORA_ZP = 0x05, // done
    INS_ORA_ZPX = 0x15, // done
    INS_ORA_ABS = 0x0D, // done
    INS_ORA_ABSX = 0x1D, // done
    INS_ORA_ABSY = 0x19, // done
    INS_ORA_INDX = 0x01, // done
    INS_ORA_INDY = 0x11, // done

    //EOR

    INS_EOR_IM = 0x49, // done
    INS_EOR_ZP = 0x45, // done
    INS_EOR_ZPX = 0x55, // done
    INS_EOR_ABS = 0x4D, // done
    INS_EOR_ABSX = 0x5D, // done
    INS_EOR_ABSY = 0x59, // done
    INS_EOR_INDX = 0x41, // done
    INS_EOR_INDY = 0x51, // done

    //BIT

    INS_BIT_ZP = 0x24, // done
    INS_BIT_ABS = 0x2C, // done

    //Transfer Registers

    INS_TAX = 0xAA, // done
    INS_TAY = 0xA8, // done
    INS_TXA = 0x8A, // done
    INS_TYA = 0x98, // done

    //Increments, Decrements

    INS_INX = 0xE8, // done
    INS_INY = 0xC8, // done
    INS_DEY = 0x88, // done
    INS_DEX = 0xCA, // done
    INS_DEC_ZP = 0xC6, // done
    INS_DEC_ZPX = 0xD6, // done
    INS_DEC_ABS = 0xCE, // done
    INS_DEC_ABSX = 0xDE, // done
    INS_INC_ZP = 0xE6, // done
    INS_INC_ZPX = 0xF6, // done
    INS_INC_ABS = 0xEE, // done
    INS_INC_ABSX = 0xFE, // done

    //branches
    INS_BEQ = 0xF0, // done
    INS_BNE = 0xD0, // done
    INS_BCS = 0xB0, // done
    INS_BCC = 0x90, // done
    INS_BMI = 0x30, // done
    INS_BPL = 0x10, // done
    INS_BVC = 0x50, // done
    INS_BVS = 0x70, // done  

    //status flag changes
    INS_CLC = 0x18, // done
    INS_SEC = 0x38, // done
    INS_CLD = 0xD8, // done
    INS_SED = 0xF8, // done
    INS_CLI = 0x58, // done
    INS_SEI = 0x78, // done
    INS_CLV = 0xB8, // done

    //Arithmetic
    INS_ADC_IM = 0x69, // done
    INS_ADC_ZP = 0x65, // done
    INS_ADC_ZPX = 0x75, // done
    INS_ADC_ABS = 0x6D, // done
    INS_ADC_ABSX = 0x7D, // done
    INS_ADC_ABSY = 0x79, // done
    INS_ADC_INDX = 0x61, 
    INS_ADC_INDY = 0x71,

    INS_SBC_IM = 0xE9, // done
    INS_SBC_ZP = 0xE5, // done
    INS_SBC_ZPX = 0xF5, // done
    INS_SBC_ABS = 0xED, // done
    INS_SBC_ABSX = 0xFD, // done
    INS_SBC_ABSY = 0xF9, // done
    INS_SBC_INDX = 0xE1, // done
    INS_SBC_INDY = 0xF1, // done

    // Register Comparison
    INS_CMP_IM = 0xC9, // done
    INS_CMP_ZP = 0xC5, // done
    INS_CMP_ZPX = 0xD5, // done
    INS_CMP_ABS = 0xCD, // done
    INS_CMP_ABSX = 0xDD, // done
    INS_CMP_ABSY = 0xD9, // done
    INS_CMP_INDX = 0xC1, // done
    INS_CMP_INDY = 0xD1, // done

    INS_CPX = 0xE0, // done
    INS_CPY = 0xC0, // done
    INS_CPX_ZP = 0xE4, // done
    INS_CPY_ZP = 0xC4, // done
    INS_CPX_ABS = 0xEC, // done
    INS_CPY_ABS = 0xCC, // done

    // shifts
    INS_ASL_ACC = 0x0A, // done
    INS_ASL_ZP = 0x06, // done
    INS_ASL_ZPX = 0x16, // done
    INS_ASL_ABS = 0x0E, // done
    INS_ASL_ABSX = 0x1E, // done

    INS_LSR = 0x4A, // done
    INS_LSR_ZP = 0x46, // done
    INS_LSR_ZPX = 0x56, // done
    INS_LSR_ABS = 0x4E, // done
    INS_LSR_ABSX = 0x5E, // done

    INS_ROL = 0x2A, // done
    INS_ROL_ZP = 0x26,  // done
    INS_ROL_ZPX = 0x36, // done
    INS_ROL_ABS = 0x2E, // done
    INS_ROL_ABSX = 0x3E,  // done

    INS_ROR = 0x6A, // done
    INS_ROR_ZP = 0x66,  // done
    INS_ROR_ZPX = 0x76, // done
    INS_ROR_ABS = 0x6E, // done
    INS_ROR_ABSX = 0x7E,  // done

    //misc
    INS_NOP = 0xEA, // done
    INS_BRK = 0x00, // done
    INS_RTI = 0x40, // done

} Instruction;


