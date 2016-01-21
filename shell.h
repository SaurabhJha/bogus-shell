#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

/* Represents file descriptor of standard input associated with shell's
   foreground process */
extern int shell_terminal;

/* Represents whether the shell file descriptor is associated with a
   foreground process */
extern bool shell_is_interactive;

/* Represents the process group of standard input associated with shell's
   foreground process*/
extern pid_t shell_pgid;

/* Represents information associated with shell's standard file
   descriptor*/
extern struct termios shell_tmodes;

int shell(int argc, char* argv[]);
