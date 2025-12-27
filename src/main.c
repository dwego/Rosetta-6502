#include "loader.h"
#include "memory_map.h"
#include "config.h"
#include "cpu_exec.h"
#include "mem6502.h"
#include "render_ram.h"
#include "mmio.h"


int
main (int argc, char *argv[])
{

  char *bin_file = NULL;
  Word load_addr = ROM_START;

  debug_set_level(DEBUG_OFF);
  CPU6502 cpu;
  MEM6502 mem;
  Bus6502 bus;
  Byte acc;

  int enable_ram_view = 0;
  char *mmio_file = NULL;

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
      if ((strcmp(argv[i], "--mmio") == 0 || strcmp(argv[i], "-m") == 0) && i + 1 < argc)
        {
            mmio_file = argv[++i];
        }

    }

  open_log ("cpu_log.txt");
  initializeMem6502 (&mem);

  if (mmio_file) {
    mmio_load_config(mmio_file);
  } else {
      mmio_load_config("./firmware/mmio.cfg");
  }


  printf("Trying to load file: %s\n", bin_file);

    if (!load_binary_to_memory(&mem, bin_file, load_addr)) {
        printf("FAILED TO LOAD FILE!!!\n");
        return 1;
    }

    printf("Load complete!\n");


    set_reset_vector(&mem, load_addr);
  resetCPU (&cpu, &mem);

  // init sync clock
  clock_init ();

  // REMOVE THIS IF YOU DON'T WANT EXIT MMIO
  while (!mmio_exit_requested && run_cpu_instruction(&bus, &mem, &cpu)) {
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

  close_log();
  return 0;
}
