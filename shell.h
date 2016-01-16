#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

/* shell terminal file descriptor */
extern int shell_terminal;

/* boolean flag for whether the terminal file descriptor is a */
/* foreground process */
extern bool shell_is_interactive;

/* process group id associated with shell terminal file descriptor */
extern pid_t shell_pgid;

/* a structure to hold information about shell terminal file descriptor */
extern struct termios shell_tmodes;

/* main shell function */
int shell(int argc, char* argv[]);
