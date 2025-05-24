/*
 * Testes da instrução ld (6502) – modos: Immediate, ZP, ZP,X
 */

#include "instructions/ld/ld_helpers.h"

const ld_case_t ld_cases[] = { { "positive", 0x10, false, false },
                               { "zero", 0x00, true, false },
                               { "negative", 0x80, false, true } };

/* ----------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------- */

/* ----------------------------------------------------------
 * Immediate ($A9)
 * ---------------------------------------------------------- */
void
test_ld_immediate (Byte *reg, Instruction ins)
{
  for (size_t i = 0; i < N_CASES; ++i)
    {
      const Byte prog[] = { ins, ld_cases[i].value };
      load_and_run (prog, sizeof prog, 2); /* ld #immediato = 2 ciclos */

      char msg[32];
      sprintf (msg, "IM %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem); /* pronto para a próxima iteração          */
    }
}

/* ----------------------------------------------------------
 * Zero Page ($A5)
 * ---------------------------------------------------------- */
void
test_ld_zp (Byte *reg, Instruction ins)
{
  const Byte zp_addr = 0x81;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      mem.Data[zp_addr] = ld_cases[i].value;

      const Byte prog[] = { ins, zp_addr };
      load_and_run (prog, sizeof prog, 3); /* ld zp = 3 ciclos */

      char msg[32];
      sprintf (msg, "ZP %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
    }
}

/* ----------------------------------------------------------
 * Zero Page,X ($B5)
 * ---------------------------------------------------------- */
void
test_ld_zpx (Byte *reg, Instruction ins)
{
  const Byte base = 0x80;
  const Byte offset = 0x01;
  const Byte addr = base + offset;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.X = offset; /* deslocamento X          */
      mem.Data[addr] = ld_cases[i].value;

      const Byte prog[] = { ins, base };
      load_and_run (prog, sizeof prog, 4); /* ld zp,X = 4 ciclos     */

      char msg[32];
      sprintf (msg, "ZPX %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
      cpu.X = 0; /* limpa X p/ próxima vez  */
    }
}

/* ----------------------------------------------------------
 * Zero Page,X ($B5)
 * ---------------------------------------------------------- */
void
test_ld_zpy (Byte *reg, Instruction ins)
{
  const Byte base = 0x80;
  const Byte offset = 0x01;
  const Byte addr = base + offset;

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.Y = offset; /* deslocamento X          */
      mem.Data[addr] = ld_cases[i].value;

      const Byte prog[] = { ins, base };
      load_and_run (prog, sizeof prog, 4); /* ld zp,X = 4 ciclos     */

      char msg[32];
      sprintf (msg, "ZPY %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
      cpu.Y = 0; /* limpa X p/ próxima vez  */
    }
}

/* ----------------------------------------------------------
 * ABS ($AD)
 * ---------------------------------------------------------- */
void
test_ld_abs (Byte *reg, Instruction ins)
{
  const Word abs_addr = 0x1234; /* endereço absoluto */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      mem.Data[abs_addr] = ld_cases[i].value;

      const Byte prog[] = { ins, (Byte)(abs_addr & 0x00FF),     /* low  */
                            (Byte)((abs_addr >> 8) & 0x00FF) }; /* high */
      load_and_run (prog, sizeof prog, 4); /* ld abs = 4 ciclos */

      char msg[32];
      sprintf (msg, "ABS %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
    }
}

/* ----------------------------------------------------------
 * ABS,X ($BD)
 * ---------------------------------------------------------- */
void
test_ld_absx (Byte *reg, Instruction ins)
{
  const Word base = 0x1230;
  const Byte off = 0x04;        /* deslocamento X que NÃO cruza página */
  const Word addr = base + off; /* endereço efetivo 0x1234 */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.X = off;
      mem.Data[addr] = ld_cases[i].value;

      const Byte prog[]
          = { ins, (Byte)(base & 0x00FF), (Byte)((base >> 8) & 0x00FF) };
      load_and_run (prog, sizeof prog,
                    4); /* ld abs,X = 4 ciclos (mesma página) */

      char msg[32];
      sprintf (msg, "ABSX %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
      cpu.X = 0;
    }
}

/* ----------------------------------------------------------
 * ABS,Y ($B9)
 * ---------------------------------------------------------- */
void
test_ld_absy (Byte *reg, Instruction ins)
{
  const Word base = 0x1230;
  const Byte off = 0x04;        /* deslocamento Y que NÃO cruza página */
  const Word addr = base + off; /* endereço efetivo 0x1234 */

  for (size_t i = 0; i < N_CASES; ++i)
    {
      cpu.Y = off;
      mem.Data[addr] = ld_cases[i].value;

      const Byte prog[]
          = { ins, (Byte)(base & 0x00FF), (Byte)((base >> 8) & 0x00FF) };
      load_and_run (prog, sizeof prog,
                    4); /* ld abs,Y = 4 ciclos (mesma página) */

      char msg[32];
      sprintf (msg, "ABSY %s", ld_cases[i].label);

      TEST_ASSERT_EQUAL_UINT8_MESSAGE (ld_cases[i].value, *reg, msg);
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectZ, cpu.Flag.Z, "Z flag");
      TEST_ASSERT_EQUAL_MESSAGE (ld_cases[i].expectN, cpu.Flag.N, "N flag");

      resetCPU (&cpu, &mem);
      cpu.Y = 0;
    }
}
