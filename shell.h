#include <stdbool.h>
#include <termios.h>
#include <sys/types.h>

extern int shell_terminal;
extern bool shell_is_interactive;
extern pid_t shell_pid;
extern struct termios shell_tmodes;
