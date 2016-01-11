#include <stdbool.h>
#include <unistd.h>
#include "shell.h"

bool shell_is_interactive;
int shell_terminal;

int main (int argc, char* argv[])
{
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);
}
