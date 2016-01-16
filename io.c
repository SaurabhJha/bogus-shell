#include <stdio.h>
#include <stdlib.h>

#include "io.h"

char *get_next_command_string()
{
  char *command_string;

  command_string = (char *) malloc(MAXLEN);
  command_string = fgets(command_string, MAXLEN, stdin);
  return command_string;
}
