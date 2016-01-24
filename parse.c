#include <stdlib.h>
#include <string.h>

#include "parse.h"

/* Get standard array of arguments that can be used in exec family
   of functions. */
token *get_arguments_array(char *command_string, token *arguments_array)
{
  token *intermediate_arguments_array, current_token;
  int i, j;

  intermediate_arguments_array = (token *) malloc(sizeof(token) * MAX_ARGUMENTS);
  current_token = strtok(command_string, TOKEN_SEPERATOR);
  intermediate_arguments_array[0] = current_token;

  i = 1;
  while ((current_token = strtok(NULL, TOKEN_SEPERATOR)) != NULL) {
    intermediate_arguments_array[i] = current_token;
    i++;
  }

  arguments_array = (token *) (malloc(sizeof(token) * (i + 1)));
  j = 0;
  while (j < i) {
    arguments_array[j] = intermediate_arguments_array[j];
    j++;
  }

  arguments_array[i] = NULL;
  free(intermediate_arguments_array);

  return arguments_array;
}
