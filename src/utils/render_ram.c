#include "render_ram.h"

void
render_ram_matrix (MEM6502 mem)
{
  initscr ();
  start_color ();
  use_default_colors ();
  init_pair (1, COLOR_RED, -1);   // Highlight for non-zero bytes
  init_pair (2, COLOR_BLACK, -1); // Headers for row/column labels

  noecho ();
  curs_set (FALSE);
  keypad (stdscr, TRUE);
  ESCDELAY = 25;

  int offset = 0; // Starting address offset for display

  while (1)
    {
      int rows, cols;
      getmaxyx (stdscr, rows, cols);

      // Determine how many memory rows and columns fit on screen
      // Reserved screen lines:
      // line 0 - title
      // line 1 - instructions
      // line 2 - column header
      // line rows-1 - user input / messages
      int display_rows = rows - 5; // leaves space for header and footer
      if (display_rows > 32)
        display_rows = 32;

      // Each memory byte occupies 3 columns (2 hex digits + space)
      // 10 extra columns are reserved for address labels
      int max_cols = (cols - 10) / 3;
      if (max_cols > 32)
        max_cols = 32;
      if (max_cols < 1)
        max_cols = 1;

      erase ();

      mvprintw (0, 0, "RAM Viewer - Base offset: 0x%04X", offset);
      mvprintw (1, 0, "Arrows: navigate | G: go to address | ESC: exit");

      // Column header (shows hex digits 00 to 1F)
      attron (COLOR_PAIR (2) | A_BOLD);
      mvprintw (2, 7, "  ");
      for (int coluna = 0; coluna < max_cols; coluna++)
        {
          mvprintw (2, 10 + coluna * 3, "%02X", coluna);
        }
      attroff (COLOR_PAIR (2) | A_BOLD);

      // Memory rows
      for (int linha = 0; linha < display_rows; linha++)
        {
          int base_addr = offset + linha * 32;
          if (base_addr >= 65536)
            break;

          // Row header: memory address label
          attron (COLOR_PAIR (2) | A_BOLD);
          mvprintw (linha + 3, 0, "0x%04X:", base_addr);
          attroff (COLOR_PAIR (2) | A_BOLD);

          for (int coluna = 0; coluna < max_cols; coluna++)
            {
              int addr = base_addr + coluna;
              if (addr >= 65536)
                continue;

              // Highlight non-zero memory values
              if (mem.Data[addr] != 0)
                attron (COLOR_PAIR (1));

              mvprintw (linha + 3, 10 + coluna * 3, "%02X", mem.Data[addr]);

              if (mem.Data[addr] != 0)
                attroff (COLOR_PAIR (1));
            }
        }

      refresh ();

      int ch = getch ();

      if (ch == 27) // ESC key: exit viewer
        break;
      else if (ch == KEY_UP) // Scroll up by full screen of rows
        {
          if (offset >= display_rows * 32)
            offset -= display_rows * 32;
        }
      else if (ch == KEY_DOWN) // Scroll down by full screen of rows
        {
          if (offset + display_rows * 32 < 65536)
            offset += display_rows * 32;
        }
      else if (ch == KEY_LEFT) // Scroll left by one column
        {
          if (offset >= max_cols)
            offset -= max_cols;
        }
      else if (ch == KEY_RIGHT) // Scroll right by one column
        {
          if (offset + max_cols < 65536)
            offset += max_cols;
        }
      else if (ch == 'g' || ch == 'G') // Go to specific address
        {
          echo ();
          curs_set (TRUE);

          // Prompt input at the bottom line
          mvprintw (rows - 1, 0, "Go to address (hex, 0x0000 to 0xFFFF): ");
          clrtoeol ();

          char hex_input[7] = { 0 }; // space for "0x" + 4 digits + '\0'
          getnstr (hex_input, 6);

          int new_offset = (int)strtol (hex_input, NULL, 16);
          new_offset &= 0xFFF0; // Align to 16-byte boundary

          if (new_offset >= 0 && new_offset < 65536)
            offset = new_offset;

          noecho ();
          curs_set (FALSE);
        }
    }

  endwin ();
}
