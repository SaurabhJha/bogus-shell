/* Word or token in input string. */
typedef char *token;

/* Tokens can be seperated by space or newline. */
#define TOKEN_SEPERATOR " \n"

/* Maximum number of arguments allowed */
#define MAX_ARGUMENTS 50

token *get_arguments_array(char *command_string, token *arguments_array);
