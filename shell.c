#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "shell.h"

int shell_terminal;
bool shell_is_interactive;
pid_t shell_pid;

int main (int argc, char *argv[])
{
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    while (tcgetpgrp(shell_terminal) != (shell_pid = getpgrp()))
      kill(-shell_pid, SIGTTIN);
    tcsetpgrp(shell_terminal, shell_pid);
  }
}
