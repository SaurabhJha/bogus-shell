#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

/* Returns pointer to the string which is the next command issued at
   the shell prompt. */
char *get_next_command_string()
{
  char *input_string, *command_string;
  int input_string_length;

  input_string = (char *) malloc(MAXLEN);
  input_string = fgets(input_string, MAXLEN, stdin);
  input_string_length = strnlen(input_string, MAXLEN);

  command_string = (char *) malloc(input_string_length);
  strcpy(command_string, input_string);

  free(input_string);

  return command_string;
}
