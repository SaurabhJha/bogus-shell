#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include "shell.h"

int shell_terminal;
bool shell_is_interactive;
pid_t shell_pgid;
struct termios shell_tmodes;

void initialize_shell()
{
  /* Checking whether standard input is associated with a */
  /* foreground terminal */
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);

  /* Kill all process groups not associated with shell terminal */
  /* file descriptor */
  while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())) {
    kill (shell_pgid, SIGTTIN);
  }

  /* Saving process group id of foreground process */
  shell_pgid = getpgrp();

  /* Put standard input file descriptor to foreground */
  tcsetpgrp(shell_terminal, shell_pgid);
  tcgetattr(shell_terminal, &shell_tmodes);
}

int shell(int argc, char* argv[])
{
  initialize_shell();

  return 0;
}
