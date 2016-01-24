#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

#include "io.h"
#include "parse.h"
#include "shell.h"

int shell_terminal;
bool shell_is_interactive;
pid_t shell_pgrp;
struct termios shell_tmodes;

/* Set basic variables to move current process to foreground so 
   that it can accept inputs. */
void initialize_shell()
{
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    /* Kill all background processes. */
    while (tcgetpgrp(shell_terminal) != (shell_pgrp = getpgrp())) {
      kill(shell_pgrp, SIGTTIN);
    }

    /* Make current process group foreground process. */
    shell_pgrp = getpgrp();
    tcsetpgrp(shell_terminal, shell_pgrp);
    tcgetattr(shell_pgrp, &shell_tmodes);
  }
}

/* Main shell loop that takes commands and tries to execute them. */
int shell(int argc, char* argv[])
{
  char *command_string, *current_path;
  token *arguments_array;
  pid_t forked_process_id;
  int forked_process_status;

  initialize_shell();

  current_path = (char *) malloc(MAX_PATH_LEN);
  current_path = getcwd(current_path, MAX_PATH_LEN);
  printf("%s%s", current_path, PROMPT);
  command_string = get_next_input();
  while (command_string != NULL) {
    arguments_array = get_arguments_array(command_string, arguments_array);

    forked_process_id = fork();
    if (forked_process_id == 0) {
      /* This is child */
      execv(arguments_array[0], arguments_array);
    } else {
      /* This is parent */
      wait(&forked_process_status);
      printf("%s%s", current_path, PROMPT);
      command_string  = get_next_input();
    }
  }
    
  return 0;
}
