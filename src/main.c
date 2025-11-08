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

  FILE *fptr;
  int enable_ram_view = 0;
  char *input_file = NULL;

  for (int i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "--ram") == 0 || strcmp (argv[i], "-r") == 0)
        {
          enable_ram_view = 1;
        }
      if (strcmp (argv[i], "--input") == 0 || strcmp (argv[i], "-i") == 0)
        {
          input_file = malloc(strlen(argv[i + 1] + 1));
          strcpy(input_file, argv[i + 1]);
          printf("%s\n", input_file);
          FILE *fptr;
          char linhas[1000][300];
          int i = 0;

          fptr = fopen(input_file, "r");
          if (fptr == NULL) {
              perror("Error to open this file");
              return 1;
          }

          while (fgets(linhas[i], MAX_LINE_SIZE, fptr) != NULL && i < MAX_LINES) {
              linhas[i][strcspn(linhas[i], "\n")] = '\0';
              i++;
          }

          fclose(fptr);

          printf("File content:\n");
          for (int j = 0; j < i; j++) {
              printf("Line %d: %s\n", j + 1, linhas[j]);
          }
        }
    }

  open_log ("cpu_log.txt");
  initializeMem6502 (&mem);

  // start - inline

  program_start = 0x8000;
  mem.Data[0xFFFC] = program_start & 0xFF;
  mem.Data[0xFFFD] = (program_start >> 8) & 0xFF;
  program_start = 0x8000;

// vetor de reset aponta para 0x8000
mem.Data[0xFFFC] = program_start & 0xFF;
mem.Data[0xFFFD] = (program_start >> 8) & 0xFF;

// programa:
mem.Data[0x8000] = INS_LDA_IM;   // opcode LDA imediato
mem.Data[0x8001] = 0xAA;         // valor 0xAA
mem.Data[0x8002] = INS_STA_ABS;  // opcode STA absoluto
mem.Data[0x8003] = 0x00;         // low byte do endereço $E000
mem.Data[0x8004] = 0xE0;         // high byte do endereço $E000
mem.Data[0x8005] = INS_BRK;  

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
  cpu_read (&bus, &mem, 0x42, &test, &cpu);
  printf ("stored value in: Accumulator is: %u\n", acc);
  printf ("stored value in Address 0x42 is: %u\n", bus.data);

  freeMem6502 (&mem);
  free(input_file);
  close_log ();
  return 0;
}
