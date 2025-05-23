#include "cpu_exec.h"

void
run_cpu_instruction (Word *Cycles, Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{

  Byte Ins = FetchByte (Cycles, bus, memory, cpu);

  switch (Ins)
    {
    /*──────────────────────────────────
      LOAD / STORE
      ──────────────────────────────────*/
    case INS_LDA_IM:
      LDA_IM (Cycles, bus, memory, cpu);
      break;
    case INS_LDA_ZP:
      LDA_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_LDA_ZPX:
      LDA_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_LDA_ABS:
      LDA_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_LDA_ABSX:
      LDA_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_LDA_ABSY:
      LDA_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_LDX_IM:
      LDX_IM (Cycles, bus, memory, cpu);
      break;
    case INS_LDX_ZP:
      LDX_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_LDX_ZPY:
      LDX_ZPY (Cycles, bus, memory, cpu);
      break;
    case INS_LDX_ABS:
      LDX_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_LDX_ABSY:
      LDX_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_LDY_IM:
      LDY_IM (Cycles, bus, memory, cpu);
      break;
    case INS_LDY_ZP:
      LDY_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_LDY_ZPX:
      LDY_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_LDY_ABS:
      LDY_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_LDY_ABSX:
      LDY_ABSX (Cycles, bus, memory, cpu);
      break;

    case INS_STA_ZP:
      STA_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_STA_ZPX:
      STA_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_STA_ABS:
      STA_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_STA_ABSX:
      STA_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_STA_ABSY:
      STA_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_STX_ZP:
      STX_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_STX_ZPY:
      STX_ZPY (Cycles, bus, memory, cpu);
      break;
    case INS_STX_ABS:
      STX_ABS (Cycles, bus, memory, cpu);
      break;

    case INS_STY_ZP:
      STY_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_STY_ZPX:
      STY_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_STY_ABS:
      STY_ABS (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      TRANSFER, STACK, MISC
      ──────────────────────────────────*/
    case INS_TSX:
      TSX (Cycles, cpu);
      break;
    case INS_TXS:
      TXS (Cycles, cpu);
      break;
    case INS_TAX:
      TAX (Cycles, cpu);
      break;
    case INS_TAY:
      TAY (Cycles, cpu);
      break;
    case INS_TXA:
      TXA (Cycles, cpu);
      break;
    case INS_TYA:
      TYA (Cycles, cpu);
      break;

    case INS_PHA:
      PHA (Cycles, bus, memory, cpu);
      break;
    case INS_PLA:
      PLA (Cycles, bus, memory, cpu);
      break;
    case INS_PHP:
      PHP (Cycles, bus, memory, cpu);
      break;
    case INS_PLP:
      PLP (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      JMP / CALL / RETURN
      ──────────────────────────────────*/
    case INS_JMP_ABS:
      JMP_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_JMP_IND:
      JMP_IND (Cycles, bus, memory, cpu);
      break;
    case INS_JSR:
      JSR (Cycles, bus, memory, cpu);
      break;
    case INS_RTS:
      RTS (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      LOGICAL  (AND / OR / EOR / BIT)
      ──────────────────────────────────*/
    case INS_AND_IM:
      AND_IM (Cycles, bus, memory, cpu);
      break;
    case INS_AND_ZP:
      AND_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_AND_ZPX:
      AND_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_AND_ABS:
      AND_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_AND_ABSX:
      AND_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_AND_ABSY:
      AND_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_ORA_IM:
      ORA_IM (Cycles, bus, memory, cpu);
      break;
    case INS_ORA_ZP:
      ORA_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_ORA_ZPX:
      ORA_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_ORA_ABS:
      ORA_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_ORA_ABSX:
      ORA_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_ORA_ABSY:
      ORA_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_EOR_IM:
      EOR_IM (Cycles, bus, memory, cpu);
      break;
    case INS_EOR_ZP:
      EOR_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_EOR_ZPX:
      EOR_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_EOR_ABS:
      EOR_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_EOR_ABSX:
      EOR_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_EOR_ABSY:
      EOR_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_BIT_ZP:
      BIT_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_BIT_ABS:
      BIT_ABS (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      INCREMENT / DECREMENT
      ──────────────────────────────────*/
    case INS_INX:
      INX (Cycles, cpu);
      break;
    case INS_INY:
      INY (Cycles, cpu);
      break;
    case INS_DEX:
      DEX (Cycles, cpu);
      break;
    case INS_DEY:
      DEY (Cycles, cpu);
      break;

    case INS_INC_ZP:
      INC_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_INC_ZPX:
      INC_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_INC_ABS:
      INC_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_INC_ABSX:
      INC_ABSX (Cycles, bus, memory, cpu);
      break;

    case INS_DEC_ZP:
      DEC_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_DEC_ZPX:
      DEC_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_DEC_ABS:
      DEC_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_DEC_ABSX:
      DEC_ABSX (Cycles, bus, memory, cpu);
      break;

      /*──────────────────────────────────
        BRANCHES
        ──────────────────────────────────
      */

    case INS_BNE:
      BNE (Cycles, bus, memory, cpu);
      break;
    case INS_BCS:
      BCS (Cycles, bus, memory, cpu);
      break;
    case INS_BCC:
      BCC (Cycles, bus, memory, cpu);
      break;
    case INS_BMI:
      BMI (Cycles, bus, memory, cpu);
      break;
    case INS_BPL:
      BPL (Cycles, bus, memory, cpu);
      break;
    case INS_BVC:
      BVC (Cycles, bus, memory, cpu);
      break;
    case INS_BVS:
      BVS (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      STATUS FLAG CHANGES
      ──────────────────────────────────*/
    case INS_CLC:
      CLC (Cycles, cpu);
      break;
    case INS_SEC:
      SEC (Cycles, cpu);
      break;
    case INS_CLD:
      CLD (Cycles, cpu);
      break;
    case INS_CLI:
      CLI (Cycles, cpu);
      break;
    case INS_SEI:
      SEI (Cycles, cpu);
      break;
    case INS_CLV:
      CLV (Cycles, cpu);
      break;

    /*──────────────────────────────────
      ARITHMETIC (ADC / SBC)
      ──────────────────────────────────*/
    case INS_ADC_IM:
      ADC_IM (Cycles, bus, memory, cpu);
      break;
    case INS_ADC_ZP:
      ADC_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_ADC_ZPX:
      ADC_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_ADC_ABS:
      ADC_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_ADC_ABSX:
      ADC_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_ADC_ABSY:
      ADC_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_SBC_IM:
      SBC_IM (Cycles, bus, memory, cpu);
      break;
    case INS_SBC_ZP:
      SBC_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_SBC_ZPX:
      SBC_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_SBC_ABS:
      SBC_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_SBC_ABSX:
      SBC_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_SBC_ABSY:
      SBC_ABSY (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      REGISTER COMPARISON
      ──────────────────────────────────*/
    case INS_CMP_IM:
      CMP_IM (Cycles, bus, memory, cpu);
      break;
    case INS_CMP_ZP:
      CMP_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_CMP_ZPX:
      CMP_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_CMP_ABS:
      CMP_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_CMP_ABSX:
      CMP_ABSX (Cycles, bus, memory, cpu);
      break;
    case INS_CMP_ABSY:
      CMP_ABSY (Cycles, bus, memory, cpu);
      break;

    case INS_CPX:
      CPX_IM (Cycles, bus, memory, cpu);
      break; /* CPX immediate */
    case INS_CPY:
      CPY_IM (Cycles, bus, memory, cpu);
      break; /* CPY immediate */
    case INS_CPX_ZP:
      CPX_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_CPY_ZP:
      CPY_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_CPX_ABS:
      CPX_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_CPY_ABS:
      CPY_ABS (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      SHIFTS / ROTATES
      ──────────────────────────────────*/
    case INS_ASL_ACC:
      ASL_ACC (Cycles, bus, memory, cpu);
      break;
    case INS_ASL_ZP:
      ASL_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_ASL_ZPX:
      ASL_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_ASL_ABS:
      ASL_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_ASL_ABSX:
      ASL_ABSX (Cycles, bus, memory, cpu);
      break;

    case INS_LSR:
      LSR_ACC (Cycles, cpu);
      break;
    case INS_LSR_ZP:
      LSR_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_LSR_ZPX:
      LSR_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_LSR_ABS:
      LSR_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_LSR_ABSX:
      LSR_ABSX (Cycles, bus, memory, cpu);
      break;

    case INS_ROL:
      ROL_ACC (Cycles, cpu);
      break;
    case INS_ROL_ZP:
      ROL_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_ROL_ZPX:
      ROL_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_ROL_ABS:
      ROL_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_ROL_ABSX:
      ROL_ABSX (Cycles, bus, memory, cpu);
      break;

    case INS_ROR:
      ROR_ACC (Cycles, cpu);
      break;
    case INS_ROR_ZP:
      ROR_ZP (Cycles, bus, memory, cpu);
      break;
    case INS_ROR_ZPX:
      ROR_ZPX (Cycles, bus, memory, cpu);
      break;
    case INS_ROR_ABS:
      ROR_ABS (Cycles, bus, memory, cpu);
      break;
    case INS_ROR_ABSX:
      ROR_ABSX (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      MISC
      ──────────────────────────────────*/
    case INS_NOP:
      NOP (Cycles);
      break;
    case INS_BRK:
      BRK (Cycles, bus, memory, cpu);
      break;

    /*──────────────────────────────────
      DEFAULT
      ──────────────────────────────────*/
    default:
      printf ("Instruction not handled 0x%02X\n", Ins);
      (*Cycles) = 0;
      break;
    }
}
