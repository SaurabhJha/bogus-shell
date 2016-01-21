#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "shell.h"
#include "io.h"

/* External variables declared at shell.h. Their purpose is explained
   at shell.h*/
int shell_terminal;
bool shell_is_interactive;
pid_t shell_pgid;
struct termios shell_tmodes;

/* Set appropriate variables to associate standard input file descriptor
   to foreground terminal process and killing all other background terminal
   proceses.*/
void initialize_shell()
{
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    /* Kill all background processes. */
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())) {
      kill(shell_pgid, SIGTTIN);
    }

    /* Bring terminal process to foreground. */
    shell_pgid = getpgrp();
    tcsetpgrp(shell_terminal, shell_pgid);
    tcgetattr(shell_terminal, &shell_tmodes);
  }
}

int shell(int argc, char* argv[])
{
  char *command_string;

  initialize_shell();

  while ((command_string = get_next_command_string()) != NULL) {
    printf("%s", command_string);
  }
  return 0;
}
