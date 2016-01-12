#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int shell_terminal, child_status;
  bool shell_is_interactive;
  pid_t shell_pgid;
  char *input_string, *command;
  struct termios shell_tmodes;
  char *arg_list[10] = {"/bin/ls"};

  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);
  if (shell_is_interactive) {
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
      kill(shell_pgid, SIGTTIN);
    shell_pgid = getpgrp();
    tcsetpgrp(shell_terminal, shell_pgid);
    tcgetattr(shell_terminal, &shell_tmodes);
  }
  input_string = (char *) malloc(1024);
  fgets(input_string, 1024, stdin);
  command = strtok(input_string, " ");
  child_status = execv(command, arg_list);
  printf("%d\n", child_status);
}
