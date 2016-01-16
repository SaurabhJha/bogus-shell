#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "io.h"
#include "shell.h"

int shell_terminal;
bool shell_is_interactive;
pid_t shell_pgid;
struct termios shell_tmodes;

/**
 * Setting standard I/O file descriptors to correct values.
 */
void initialize_shell()
{
  /* Checking whether standard input is associated with a */
  /* foreground terminal */
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);

  /* Kill all process groups not associated with shell terminal */
  /* file descriptor */
  while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())) {
    kill(shell_pgid, SIGTTIN);
  }

  /* Process group id of foreground process */
  shell_pgid = getpgrp();

  /* Put standard input file descriptor to foreground */
  tcsetpgrp(shell_terminal, shell_pgid);
  tcgetattr(shell_terminal, &shell_tmodes);
}

/**
 * Core shell logic
 */
int shell(int argc, char* argv[])
{
  char *command_string;

  initialize_shell();

  while ((command_string = get_next_command_string())) {
    printf("%s", command_string);
  }
  return 0;
}
