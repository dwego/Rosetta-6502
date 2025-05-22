#include "config.h"

FILE *log_file = NULL;

void
open_log (const char *filename)
{
  log_file = fopen (filename, "w");
  if (log_file == NULL)
    {
      perror ("Failed to open log file");
    }
}

void
close_log (void)
{
  if (log_file != NULL)
    {
      fclose (log_file);
      log_file = NULL;
    }
}
