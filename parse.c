#include <string.h>

#include "parse.h"

/* Takes command string from standard input as argument and creates
   an array of token strings. The array of arguments is passed as
   second argument. The command string is divided by spaces and
   newlines. */
void get_array_of_arguments(char *command_string, command_token *array_of_arguments)
{
  command_token current_token;
  int i;

  array_of_arguments[0] = strtok(command_string, TOKEN_SEPERATOR);
  i = 1;
  while ((current_token = strtok(NULL, TOKEN_SEPERATOR)) != NULL) {
    array_of_arguments[i] = current_token;
    i += 1;
  }
  array_of_arguments[i] = NULL;
}
