#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

/* File descriptor associated with standard input. */
extern int shell_terminal;

/* Whether current process group is associated with standard input. */
extern bool shell_is_interactive;

/* Current process group. */
extern pid_t shell_pgrp;

/* Settings corresponding to terminal device. */
extern struct termios shell_tmodes;

/* Maximum current path length */
#define MAX_PATH_LEN 50

/* Prompt symbol*/
#define PROMPT "=>"

void initialize_shell();

int shell(int argc, char* argv[]);
