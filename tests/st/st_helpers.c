/*
 * Testes da instrução st (6502) – modos: Immediate, ZP, ZP,X
 */

#include "instructions/st/st_helpers.h"

const st_case_t st_cases[]
    = { { "positive", 0x10 }, { "zero", 0x00 }, { "negative", 0x80 } };

/* ----------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------- */
/* ----------------------------------------------------------
 * Zero Page ($A5)
 * ---------------------------------------------------------- */
void
test_st_zp (Byte *reg, Instruction ins)
{
  const Byte zp_addr = 0x20;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      *reg = st_cases[i].value;
      mem.Data[zp_addr] = 0xFF;

      const Byte prog[] = { ins, zp_addr };
      load_and_run (prog, sizeof prog, 3); /* st zp = 3 ciclos */

      char msg[32];
      sprintf (msg, "ZP %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[zp_addr],
                                       msg);

      resetCPU (&cpu, &mem);
    }
}

/* ----------------------------------------------------------
 * Zero Page,X ($B5)
 * ---------------------------------------------------------- */
void
test_st_zpx (Byte *reg, Instruction ins)
{
  const Byte base = 0x20;
  const Byte offset = 0x01;
  const Byte addr = base + offset;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.X = offset;
      *reg = st_cases[i].value;

      const Byte prog[] = { ins, base };
      load_and_run (prog, sizeof prog, 4); /* st zp,X = 4 ciclos     */

      char msg[32];
      sprintf (msg, "ZPX %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[addr], msg);
      resetCPU (&cpu, &mem);
      cpu.X = 0; /* limpa X p/ próxima vez  */
    }
}

/* ----------------------------------------------------------
 * Zero Page,X ($B5)
 * ---------------------------------------------------------- */
void
test_st_zpy (Byte *reg, Instruction ins)
{
  const Byte base = 0x80;
  const Byte offset = 0x01;
  const Byte addr = base + offset;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.Y = offset;
      *reg = st_cases[i].value;

      const Byte prog[] = { ins, base };
      load_and_run (prog, sizeof prog, 4); /* st zp,X = 4 ciclos     */

      char msg[32];
      sprintf (msg, "ZPY %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[addr], msg);

      resetCPU (&cpu, &mem);
      cpu.Y = 0;
    }
}

/* ----------------------------------------------------------
 * ABS ($AD)
 * ---------------------------------------------------------- */
void
test_st_abs (Byte *reg, Instruction ins)
{
  const Word abs_addr = 0x1234; /* endereço absoluto */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      *reg = st_cases[i].value;

      const Byte prog[] = { ins, (Byte)(abs_addr & 0x00FF),     /* low  */
                            (Byte)((abs_addr >> 8) & 0x00FF) }; /* high */
      load_and_run (prog, sizeof prog, 4); /* st abs = 4 ciclos */

      char msg[32];
      sprintf (msg, "ABS %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[abs_addr],
                                       msg);

      resetCPU (&cpu, &mem);
    }
}

/* ----------------------------------------------------------
 * ABS,X ($BD)
 * ---------------------------------------------------------- */
void
test_st_absx (Byte *reg, Instruction ins)
{
  const Word base = 0x1230;
  const Byte off = 0x04;        /* deslocamento X que NÃO cruza página */
  const Word addr = base + off; /* endereço efetivo 0x1234 */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.X = off;
      *reg = st_cases[i].value;

      const Byte prog[]
          = { ins, (Byte)(base & 0x00FF), (Byte)((base >> 8) & 0x00FF) };
      load_and_run (prog, sizeof prog,
                    4); /* st abs,X = 4 ciclos (mesma página) */

      char msg[32];
      sprintf (msg, "ABSX %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[addr], msg);

      resetCPU (&cpu, &mem);
      cpu.X = 0;
    }
}

/* ----------------------------------------------------------
 * ABS,Y ($B9)
 * ---------------------------------------------------------- */
void
test_st_absy (Byte *reg, Instruction ins)
{
  const Word base = 0x1230;
  const Byte off = 0x04;        /* deslocamento Y que NÃO cruza página */
  const Word addr = base + off; /* endereço efetivo 0x1234 */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.Y = off;
      *reg = st_cases[i].value;

      const Byte prog[]
          = { ins, (Byte)(base & 0x00FF), (Byte)((base >> 8) & 0x00FF) };
      load_and_run (prog, sizeof prog,
                    4); /* st abs,Y = 4 ciclos (mesma página) */

      char msg[32];
      sprintf (msg, "ABSY %s", st_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (st_cases[i].value, mem.Data[addr], msg);

      resetCPU (&cpu, &mem);
      cpu.Y = 0;
    }
}
