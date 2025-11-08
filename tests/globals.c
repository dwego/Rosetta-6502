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

  clock_init ();
  while (1)
    run_cpu_instruction (&cycles, &bus, &mem, &cpu);
}

void
setUp (void)
{
  open_log ("../cpu_log.txt");
  initializeMem6502 (&mem);
  mem.Data[0xFFFC] = 0x00;
  mem.Data[0xFFFD] = 0x80;
  resetCPU (&cpu, &mem);
  cycles = 20;
}

void
tearDown (void)
{
  freeMem6502 (&mem);
  close_log ();
}
