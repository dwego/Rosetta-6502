#include "cpu_exec.h"
#include "cpu6502.h"
#include <stdio.h>

static AccessType
get_instruction_access_type (Byte opcode)
{
    switch (opcode)
    {
        /* ────────────────
           Read memory (RAM/MMIO)
           ──────────────── */
        case INS_LDA_IM: case INS_LDA_ZP: case INS_LDA_ABS: case INS_LDA_ABSX: case INS_LDA_ABSY:
        case INS_LDA_ZPX: case INS_LDA_INDX: case INS_LDA_INDY:        // LDA
        case INS_LDX_IM: case INS_LDX_ZP: case INS_LDX_ABS: case INS_LDX_ZPY: case INS_LDX_ABSY: // LDX
        case INS_LDY_IM: case INS_LDY_ZP: case INS_LDY_ABS: case INS_LDY_ABSX: case INS_LDY_ZPX: // LDY
        case INS_ADC_IM: case INS_ADC_ZP: case INS_ADC_ABS: case INS_ADC_ABSX: case INS_ADC_ABSY:
        case INS_ADC_ZPX: case INS_ADC_INDX: case INS_ADC_INDY:        // ADC
        case INS_SBC_IM: case INS_SBC_ZP: case INS_SBC_ABS: case INS_SBC_ABSX: case INS_SBC_ABSY:
        case INS_SBC_ZPX: case INS_SBC_INDX: case INS_SBC_INDY:        // SBC
        case INS_CMP_IM: case INS_CMP_ZP: case INS_CMP_ABS: case INS_CMP_ABSX: case INS_CMP_ABSY:
        case INS_CMP_ZPX: case INS_CMP_INDX: case INS_CMP_INDY:        // CMP
        case INS_CPX: case INS_CPX_ZP: case INS_CPX_ABS:            // CPX
        case INS_CPY: case INS_CPY_ZP: case INS_CPY_ABS:            // CPY
        case INS_BIT_ZP: case INS_BIT_ABS:                             // BIT
            return ACCESS_RAM | ACCESS_MMIO;

        /* ────────────────
           Escrita em memória (RAM/MMIO)
           ──────────────── */
        case INS_STA_ZP: case INS_STA_ZPX: case INS_STA_ABS: case INS_STA_ABSX: case INS_STA_ABSY:
        case INS_STA_INDX: case INS_STA_INDY:        // STA
        case INS_STX_ZP: case INS_STX_ZPY: case INS_STX_ABS:        // STX
        case INS_STY_ZP: case INS_STY_ZPX: case INS_STY_ABS:        // STY
        case INS_INC_ZP: case INS_INC_ZPX: case INS_INC_ABS: case INS_INC_ABSX: // INC
        case INS_DEC_ZP: case INS_DEC_ZPX: case INS_DEC_ABS: case INS_DEC_ABSX: // DEC
        case INS_ASL_ZP: case INS_ASL_ZPX: case INS_ASL_ABS: case INS_ASL_ABSX: // ASL
        case INS_LSR_ZP: case INS_LSR_ZPX: case INS_LSR_ABS: case INS_LSR_ABSX: // LSR
        case INS_ROL_ZP: case INS_ROL_ZPX: case INS_ROL_ABS: case INS_ROL_ABSX: // ROL
        case INS_ROR_ZP: case INS_ROR_ZPX: case INS_ROR_ABS: case INS_ROR_ABSX: // ROR
            return ACCESS_RAM | ACCESS_MMIO;

        /* ────────────────
           Stack / sistema (RAM)
           ──────────────── */
        case INS_PHP: case INS_PLP:                   // PHP, PLP
        case INS_PHA: case INS_PLA:                   // PHA, PLA
        case INS_BRK:                              // BRK
        case INS_JSR: case INS_RTS:                   // JSR, RTS
        case INS_RTI:                              // RTI
            return ACCESS_RAM;

        /* ────────────────
           Controle interno / flags / registradores
           ──────────────── */
        case INS_CLC: case INS_SEC:                   // CLC, SEC
        case INS_CLI: case INS_SEI:                   // CLI, SEI
        case INS_CLV:                              // CLV
        case INS_CLD: case INS_SED:                   // CLD, SED
        case INS_NOP:                              // NOP
        case INS_TAX: case INS_TAY: case INS_TXA: case INS_TYA: // TAX,TAY,TXA,TYA
        case INS_TSX: case INS_TXS:                   // TSX,TXS
        case INS_DEX: case INS_DEY:                   // DEX,DEY
        case INS_INX: case INS_INY:                   // INX,INY
            return ACCESS_NONE;

        /* ────────────────
           Branches e jumps (somente leitura de PC/ROM)
           ──────────────── */
        case INS_JMP_ABS: case INS_JMP_IND:                   // JMP abs, ind
        case INS_BPL: case INS_BMI: case INS_BVC: case INS_BVS:
        case INS_BCC: case INS_BCS: case INS_BNE: case INS_BEQ: // branches
            return ACCESS_NONE; // ROM é usada no fetch, não aqui

        default:
            // Instrução não reconhecida (ou futura expansão)
            return ACCESS_NONE;
    }
}


bool
run_cpu_instruction (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
{

  Byte Ins = FetchByte (bus, memory, cpu);
  AccessType accessType = get_instruction_access_type (Ins);
  cpu->CurrentAccess = accessType;
  

  switch (Ins)
    {
    /*──────────────────────────────────
      LOAD / STORE
      ──────────────────────────────────*/
    case INS_LDA_IM:
      LDA_IM (bus, memory, cpu);
      break;
    case INS_LDA_ZP:
      LDA_ZP (bus, memory, cpu);
      break;
    case INS_LDA_ZPX:
      LDA_ZPX (bus, memory, cpu);
      break;
    case INS_LDA_ABS:
      LDA_ABS (bus, memory, cpu);
      break;
    case INS_LDA_ABSX:
      LDA_ABSX (bus, memory, cpu);
      break;
    case INS_LDA_ABSY:
      LDA_ABSY (bus, memory, cpu);
      break;
    case INS_LDA_INDX:
      LDA_INDX (bus, memory, cpu);
      break;
    case INS_LDA_INDY:
      LDA_INDY (bus, memory, cpu);
      break;

    case INS_LDX_IM:
      LDX_IM (bus, memory, cpu);
      break;
    case INS_LDX_ZP:
      LDX_ZP (bus, memory, cpu);
      break;
    case INS_LDX_ZPY:
      LDX_ZPY (bus, memory, cpu);
      break;
    case INS_LDX_ABS:
      LDX_ABS (bus, memory, cpu);
      break;
    case INS_LDX_ABSY:
      LDX_ABSY (bus, memory, cpu);
      break;

    case INS_LDY_IM:
      LDY_IM (bus, memory, cpu);
      break;
    case INS_LDY_ZP:
      LDY_ZP (bus, memory, cpu);
      break;
    case INS_LDY_ZPX:
      LDY_ZPX (bus, memory, cpu);
      break;
    case INS_LDY_ABS:
      LDY_ABS (bus, memory, cpu);
      break;
    case INS_LDY_ABSX:
      LDY_ABSX (bus, memory, cpu);
      break;

    case INS_STA_ZP:
      STA_ZP (bus, memory, cpu);
      break;
    case INS_STA_ZPX:
      STA_ZPX (bus, memory, cpu);
      break;
    case INS_STA_ABS:
      STA_ABS (bus, memory, cpu);
      break;
    case INS_STA_ABSX:
      STA_ABSX (bus, memory, cpu);
      break;
    case INS_STA_ABSY:
      STA_ABSY (bus, memory, cpu);
      break;
    case INS_STA_INDX:
      STA_INDX (bus, memory, cpu);
      break;
    case INS_STA_INDY:
      STA_INDY (bus, memory, cpu);
      break;

    case INS_STX_ZP:
      STX_ZP (bus, memory, cpu);
      break;
    case INS_STX_ZPY:
      STX_ZPY (bus, memory, cpu);
      break;
    case INS_STX_ABS:
      STX_ABS (bus, memory, cpu);
      break;

    case INS_STY_ZP:
      STY_ZP (bus, memory, cpu);
      break;
    case INS_STY_ZPX:
      STY_ZPX (bus, memory, cpu);
      break;
    case INS_STY_ABS:
      STY_ABS (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      TRANSFER, STACK, MISC
      ──────────────────────────────────*/
    case INS_TSX:
      TSX (cpu);
      break;
    case INS_TXS:
      TXS (cpu);
      break;
    case INS_TAX:
      TAX (cpu);
      break;
    case INS_TAY:
      TAY (cpu);
      break;
    case INS_TXA:
      TXA (cpu);
      break;
    case INS_TYA:
      TYA (cpu);
      break;

    case INS_PHA:
      PHA (bus, memory, cpu);
      break;
    case INS_PLA:
      PLA (bus, memory, cpu);
      break;
    case INS_PHP:
      PHP (bus, memory, cpu);
      break;
    case INS_PLP:
      PLP (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      JMP / CALL / RETURN
      ──────────────────────────────────*/
    case INS_JMP_ABS:
      JMP_ABS (bus, memory, cpu);
      break;
    case INS_JMP_IND:
      JMP_IND (bus, memory, cpu);
      break;
    case INS_JSR:
      JSR (bus, memory, cpu);
      break;
    case INS_RTS:
      RTS (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      LOGICAL  (AND / OR / EOR / BIT)
      ──────────────────────────────────*/
    case INS_AND_IM:
      AND_IM (bus, memory, cpu);
      break;
    case INS_AND_ZP:
      AND_ZP (bus, memory, cpu);
      break;
    case INS_AND_ZPX:
      AND_ZPX (bus, memory, cpu);
      break;
    case INS_AND_ABS:
      AND_ABS (bus, memory, cpu);
      break;
    case INS_AND_ABSX:
      AND_ABSX (bus, memory, cpu);
      break;
    case INS_AND_ABSY:
      AND_ABSY (bus, memory, cpu);
      break;
    case INS_AND_INDX:
      AND_INDX (bus, memory, cpu);
      break;
    case INS_AND_INDY:
      AND_INDY (bus, memory, cpu);
      break;
    

    case INS_ORA_IM:
      ORA_IM (bus, memory, cpu);
      break;
    case INS_ORA_ZP:
      ORA_ZP (bus, memory, cpu);
      break;
    case INS_ORA_ZPX:
      ORA_ZPX (bus, memory, cpu);
      break;
    case INS_ORA_ABS:
      ORA_ABS (bus, memory, cpu);
      break;
    case INS_ORA_ABSX:
      ORA_ABSX (bus, memory, cpu);
      break;
    case INS_ORA_ABSY:
      ORA_ABSY (bus, memory, cpu);
      break;
    case INS_ORA_INDX:
      ORA_INDX (bus, memory, cpu);
      break;
    case INS_ORA_INDY:
      ORA_INDY (bus, memory, cpu);
      break;

    case INS_EOR_IM:
      EOR_IM (bus, memory, cpu);
      break;
    case INS_EOR_ZP:
      EOR_ZP (bus, memory, cpu);
      break;
    case INS_EOR_ZPX:
      EOR_ZPX (bus, memory, cpu);
      break;
    case INS_EOR_ABS:
      EOR_ABS (bus, memory, cpu);
      break;
    case INS_EOR_ABSX:
      EOR_ABSX (bus, memory, cpu);
      break;
    case INS_EOR_ABSY:
      EOR_ABSY (bus, memory, cpu);
      break;
    case INS_EOR_INDX:
      EOR_INDX (bus, memory, cpu);
      break;
    case INS_EOR_INDY:
      EOR_INDY (bus, memory, cpu);
      break;

    case INS_BIT_ZP:
      BIT_ZP (bus, memory, cpu);
      break;
    case INS_BIT_ABS:
      BIT_ABS (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      INCREMENT / DECREMENT
      ──────────────────────────────────*/
    case INS_INX:
      INX (cpu);
      break;
    case INS_INY:
      INY (cpu);
      break;
    case INS_DEX:
      DEX (cpu);
      break;
    case INS_DEY:
      DEY (cpu);
      break;

    case INS_INC_ZP:
      INC_ZP (bus, memory, cpu);
      break;
    case INS_INC_ZPX:
      INC_ZPX (bus, memory, cpu);
      break;
    case INS_INC_ABS:
      INC_ABS (bus, memory, cpu);
      break;
    case INS_INC_ABSX:
      INC_ABSX (bus, memory, cpu);
      break;

    case INS_DEC_ZP:
      DEC_ZP (bus, memory, cpu);
      break;
    case INS_DEC_ZPX:
      DEC_ZPX (bus, memory, cpu);
      break;
    case INS_DEC_ABS:
      DEC_ABS (bus, memory, cpu);
      break;
    case INS_DEC_ABSX:
      DEC_ABSX (bus, memory, cpu);
      break;

      /*──────────────────────────────────
        BRANCHES
        ──────────────────────────────────
      */

    case INS_BNE:
      BNE (bus, memory, cpu);
      break;
    case INS_BCS:
      BCS (bus, memory, cpu);
      break;
    case INS_BCC:
      BCC (bus, memory, cpu);
      break;
    case INS_BMI:
      BMI (bus, memory, cpu);
      break;
    case INS_BPL:
      BPL (bus, memory, cpu);
      break;
    case INS_BVC:
      BVC (bus, memory, cpu);
      break;
    case INS_BVS:
      BVS (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      STATUS FLAG CHANGES
      ──────────────────────────────────*/
    case INS_CLC:
      CLC (cpu);
      break;
    case INS_SEC:
      SEC (cpu);
      break;
    case INS_CLD:
      CLD (cpu);
      break;
    case INS_CLI:
      CLI (cpu);
      break;
    case INS_SEI:
      SEI (cpu);
      break;
    case INS_CLV:
      CLV (cpu);
      break;

    /*──────────────────────────────────
      ARITHMETIC (ADC / SBC)
      ──────────────────────────────────*/
    case INS_ADC_IM:
      ADC_IM (bus, memory, cpu);
      break;
    case INS_ADC_ZP:
      ADC_ZP (bus, memory, cpu);
      break;
    case INS_ADC_ZPX:
      ADC_ZPX (bus, memory, cpu);
      break;
    case INS_ADC_ABS:
      ADC_ABS (bus, memory, cpu);
      break;
    case INS_ADC_ABSX:
      ADC_ABSX (bus, memory, cpu);
      break;
    case INS_ADC_ABSY:
      ADC_ABSY (bus, memory, cpu);
      break;
    case INS_ADC_INDX:
      ADC_INDX (bus, memory, cpu);
      break;
    case INS_ADC_INDY:
      ADC_INDY (bus, memory, cpu);
      break;

    case INS_SBC_IM:
      SBC_IM (bus, memory, cpu);
      break;
    case INS_SBC_ZP:
      SBC_ZP (bus, memory, cpu);
      break;
    case INS_SBC_ZPX:
      SBC_ZPX (bus, memory, cpu);
      break;
    case INS_SBC_ABS:
      SBC_ABS (bus, memory, cpu);
      break;
    case INS_SBC_ABSX:
      SBC_ABSX (bus, memory, cpu);
      break;
    case INS_SBC_ABSY:
      SBC_ABSY (bus, memory, cpu);
      break;
    case INS_SBC_INDX:
      SBC_INDX (bus, memory, cpu);
      break;
    case INS_SBC_INDY:
      SBC_INDY (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      REGISTER COMPARISON
      ──────────────────────────────────*/
    case INS_CMP_IM:
      CMP_IM (bus, memory, cpu);
      break;
    case INS_CMP_ZP:
      CMP_ZP (bus, memory, cpu);
      break;
    case INS_CMP_ZPX:
      CMP_ZPX (bus, memory, cpu);
      break;
    case INS_CMP_ABS:
      CMP_ABS (bus, memory, cpu);
      break;
    case INS_CMP_ABSX:
      CMP_ABSX (bus, memory, cpu);
      break;
    case INS_CMP_ABSY:
      CMP_ABSY (bus, memory, cpu);
      break;
    case INS_CMP_INDX:
      CMP_INDX (bus, memory, cpu);
      break;
    case INS_CMP_INDY:
      CMP_INDY (bus, memory, cpu);
      break;

    case INS_CPX:
      CPX_IM (bus, memory, cpu);
      break; /* CPX immediate */
    case INS_CPY:
      CPY_IM (bus, memory, cpu);
      break; /* CPY immediate */
    case INS_CPX_ZP:
      CPX_ZP (bus, memory, cpu);
      break;
    case INS_CPY_ZP:
      CPY_ZP (bus, memory, cpu);
      break;
    case INS_CPX_ABS:
      CPX_ABS (bus, memory, cpu);
      break;
    case INS_CPY_ABS:
      CPY_ABS (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      SHIFTS / ROTATES
      ──────────────────────────────────*/
    case INS_ASL_ACC:
      ASL_ACC (bus, memory, cpu);
      break;
    case INS_ASL_ZP:
      ASL_ZP (bus, memory, cpu);
      break;
    case INS_ASL_ZPX:
      ASL_ZPX (bus, memory, cpu);
      break;
    case INS_ASL_ABS:
      ASL_ABS (bus, memory, cpu);
      break;
    case INS_ASL_ABSX:
      ASL_ABSX (bus, memory, cpu);
      break;

    case INS_LSR:
      LSR_ACC (cpu);
      break;
    case INS_LSR_ZP:
      LSR_ZP (bus, memory, cpu);
      break;
    case INS_LSR_ZPX:
      LSR_ZPX (bus, memory, cpu);
      break;
    case INS_LSR_ABS:
      LSR_ABS (bus, memory, cpu);
      break;
    case INS_LSR_ABSX:
      LSR_ABSX (bus, memory, cpu);
      break;

    case INS_ROL:
      ROL_ACC (cpu);
      break;
    case INS_ROL_ZP:
      ROL_ZP (bus, memory, cpu);
      break;
    case INS_ROL_ZPX:
      ROL_ZPX (bus, memory, cpu);
      break;
    case INS_ROL_ABS:
      ROL_ABS (bus, memory, cpu);
      break;
    case INS_ROL_ABSX:
      ROL_ABSX (bus, memory, cpu);
      break;

    case INS_ROR:
      ROR_ACC (cpu);
      break;
    case INS_ROR_ZP:
      ROR_ZP (bus, memory, cpu);
      break;
    case INS_ROR_ZPX:
      ROR_ZPX (bus, memory, cpu);
      break;
    case INS_ROR_ABS:
      ROR_ABS (bus, memory, cpu);
      break;
    case INS_ROR_ABSX:
      ROR_ABSX (bus, memory, cpu);
      break;

    /*──────────────────────────────────
      MISC
      ──────────────────────────────────*/
    case INS_RTI:
      RTI (bus, memory, cpu);
      break;
    case INS_NOP:
      NOP ();
      break;
    case INS_BRK:
      BRK (bus, memory, cpu);
      return false;
      break;

    /*──────────────────────────────────
      DEFAULT
      ──────────────────────────────────*/
    default:
      printf ("Instruction not handled 0x%02X\n", Ins);
      break;
    }
    
    // do NOT clear MMIO access
    // leave accessType as-is
    // cpu->CurrentAccess = accessType;

    
    return true;
}
