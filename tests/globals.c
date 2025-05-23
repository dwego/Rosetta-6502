#include "test_template.h"

CPU6502 cpu;
Bus6502 bus;
MEM6502 mem;
Word cycles;

/* Copia o programa para $8000, ajusta cycles e executa até zerar */
void
load_and_run (const Byte *prog, size_t len, Word expected_cycles)
{
  if (!mem.Data)
    {
      fprintf (stderr, "Erro: memória não alocada!\n");
      exit (1);
    }

  memcpy (&mem.Data[0x8000], prog, len);
  cycles = expected_cycles;

  clock_init ();
  while (cycles)
    run_cpu_instruction (&cycles, &bus, &mem, &cpu);
}
