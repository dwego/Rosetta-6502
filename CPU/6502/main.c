#include "cpu_exec.h"

int
main (void)
{
  int program_start;
  CPU6502 cpu;
  MEM6502 mem;
  Byte test;
  Word Cycles = 20;

  open_log ("cpu_log.txt");
  initializeMem6502 (&mem);
  // start - inline

  program_start = 0x8000;
  mem.Data[0xFFFC] = program_start & 0xFF;
  mem.Data[0xFFFD] = (program_start >> 8) & 0xFF;
  mem.Data[0xFFFE] = 0x10;
  mem.Data[0xFFFF] = 0x80;

  mem.Data[0x8000] = INS_LDA_IM;
  mem.Data[0x8001] = 0x10;
  mem.Data[0x8002] = INS_STA_ZP;
  mem.Data[0x8003] = 0x42;
  mem.Data[0x8004] = INS_BRK;

  // Break ASM because "0x02" isn't a instruction
  mem.Data[0x8010] = 0x02;

  // printf ("PC before reset: 0x%04X\n", cpu.PC);
  resetCPU (&cpu, &mem);
  // printf ("PC after reset: 0x%04X\n", cpu.PC);
  // end - inline a little program

  // init sync clock
  clock_init ();

  run_cpu_instruction (&Cycles, &mem, &cpu);

  if (Cycles == 0)
    {
      goto end;
    }

end:
  test = cpu.A;
  printf ("stored value in: Accumulator is: %u\n", test);
  freeMem6502 (&mem);
  close_log ();
  return 0;
}
