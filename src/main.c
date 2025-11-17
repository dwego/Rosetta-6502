#include "loader.h"
#include "memory_map.h"
#include "config.h"
#include "cpu_exec.h"
#include "mem6502.h"
#include "render_ram.h"

int
main (int argc, char *argv[])
{
  char *bin_file = NULL;
  Word load_addr = ROM_START;

  int program_start;
  CPU6502 cpu;
  MEM6502 mem;
  Bus6502 bus;
  Byte acc;

  FILE *fptr;
  int enable_ram_view = 0;
  char *input_file = NULL;

  for (int i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "--ram") == 0 || strcmp (argv[i], "-r") == 0)
        {
          enable_ram_view = 1;
        }
      if ((strcmp(argv[i], "--bin") == 0 || strcmp(argv[i], "-b") == 0) && i + 1 < argc)
        {
            bin_file = argv[++i];
        }

    }

  open_log ("cpu_log.txt");
  initializeMem6502 (&mem);

  // start - inline

  printf("Trying to load file: %s\n", bin_file);

    if (!load_binary_to_memory(&mem, bin_file, load_addr)) {
        printf("FAILED TO LOAD FILE!!!\n");
        return 1;
    }

    printf("Load complete!\n");


    set_reset_vector(&mem, load_addr);
  

  printf("Memory[E007] BEFORE EXEC: %02X\n", mem.Data[0xE007]);
  printf("Memory[E008] BEFORE EXEC: %02X\n", mem.Data[0xE008]);
  printf("Memory[E009] BEFORE EXEC: %02X\n", mem.Data[0xE009]);

  // printf ("PC before reset: 0x%04X\n", cpu.PC);
  resetCPU (&cpu, &mem);
  // printf ("PC after reset: 0x%04X\n", cpu.PC);
  // end - inline a little program

  // init sync clock
  clock_init ();

  while (run_cpu_instruction(&bus, &mem, &cpu)) {
    printf("PC=%04X A=%02X X=%02X Y=%02X SP=%02X\n",
           cpu.PC, cpu.A, cpu.X, cpu.Y, cpu.SP);
  }


  if (enable_ram_view)
    {
      render_ram_matrix (mem);
    }

  goto end;

end:
  acc = cpu.A;

  cpu_read(&bus, &mem, 0x42, &cpu);

  freeMem6502(&mem);

  if (input_file)
      free(input_file);

  close_log();
  return 0;
}
