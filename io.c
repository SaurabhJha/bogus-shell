#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

/* Get next line of input from shell terminal. */
char *get_next_input()
{
  char *input_command, *command_string;
  int input_command_length;

  input_command = (char *) malloc(MAX_COMMAND_LEN);
  input_command = fgets(input_command, MAX_COMMAND_LEN, stdin);

  input_command_length = strlen(input_command);
  command_string = (char *) malloc(input_command_length);
  command_string = strcpy(command_string, input_command);

  free(input_command);

  return command_string;
}
