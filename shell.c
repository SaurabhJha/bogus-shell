#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>

#include "shell.h"
#include "parse.h"
#include "io.h"

/* External variables declared at shell.h. Their purpose is explained
   at shell.h */
int shell_terminal;
bool shell_is_interactive;
pid_t shell_pgid;
struct termios shell_tmodes;

/* Set appropriate variables to associate standard input file descriptor
   to foreground terminal process and killing all other background terminal
   proceses. */
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
  char *command_string, *path_name;
  command_token array_of_arguments[MAXLEN];
  pid_t result_of_fork;
  int execution_status;

  initialize_shell();

  /* First prompt after the starting of shell. */
  /* Assumption: The maximum length of a path name is 50 */
  path_name = malloc(50);
  path_name = getcwd(path_name, 50);
  printf("%s:", path_name);
  command_string = get_next_command_string();

  while (command_string != NULL) {
    get_array_of_arguments(command_string, array_of_arguments);
    if (array_of_arguments[0] != NULL) {
      result_of_fork = fork();
      if (result_of_fork == 0) {
        /* This is child process. */
        execv(array_of_arguments[0], array_of_arguments);
      } else {
        /* This is parent process. */
        wait(&execution_status);
      }
    }

    printf("%s:", path_name);
    command_string = get_next_command_string();
  }
  return 0;
}
