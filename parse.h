/* Maximum number of arguments supported */
#define MAXLEN 1024

/* Allowed token seperators */
#define TOKEN_SEPERATOR " \n"

/* Represents a word or a token in a command string */
typedef char *command_token;

void get_array_of_arguments(char *command_string, command_token *array_of_arguments);
