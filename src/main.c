#include "config.h"
#include "cpu_exec.h"
#include "mem6502.h"
#include <stdio.h>

int
main (void)
{
  int program_start;
  CPU6502 cpu;
  MEM6502 mem;
  Bus6502 bus;
  Word test;
  Byte acc;
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

  while (Cycles > 0)
    {
      run_cpu_instruction (&Cycles, &bus, &mem, &cpu);
    }
  goto end;

end:
  test = 15;
  acc = cpu.A;
  cpu_read (&bus, &mem, 0x42, &test);
  printf ("stored value in: Accumulator is: %u\n", acc);
  printf ("stored value in Address 0x42 is: %u\n", bus.data);

  freeMem6502 (&mem);
  close_log ();
  return 0;
}
