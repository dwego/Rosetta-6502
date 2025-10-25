#include "config.h"
#include "cpu_exec.h"
#include "mem6502.h"
#include "render_ram.h"

int
main (int argc, char *argv[])
{
  int program_start;
  CPU6502 cpu;
  MEM6502 mem;
  Bus6502 bus;
  Word test;
  Byte acc;
  Word Cycles = 20;

  int enable_ram_view = 0;

  for (int i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "--ram") == 0 || strcmp (argv[i], "-r") == 0)
        {
          enable_ram_view = 1;
        }
    }

  open_log ("cpu_log.txt");
  initializeMem6502 (&mem);

  // start - inline

  program_start = 0x8000;
  mem.Data[0xFFFC] = program_start & 0xFF;
  mem.Data[0xFFFD] = (program_start >> 8) & 0xFF;
  mem.Data[0xFFFE] = 0x10;
  mem.Data[0xFFFF] = 0x80;

  mem.Data[0x8000] = INS_BRK;
  mem.Data[0x8001] = 0x00;
  mem.Data[0x8002] = INS_PHA;
  mem.Data[0x8003] = INS_LDA_IM;
  mem.Data[0x8004] = 0x20;
  mem.Data[0x8005] = INS_PHA;
  mem.Data[0x8006] = INS_STA_ZP;
  mem.Data[0x8007] = 0x42;
  mem.Data[0x8008] = 0x02;

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

  if (enable_ram_view)
    {
      render_ram_matrix (mem);
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
