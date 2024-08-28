#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_TOKENS 64  /* Maximum number of tokens in a command */
#define DELIMITERS " \t\r\n\a"  /* Delimiters for tokenizing commands */

/* Function Prototypes */
void prompt(void);
char *read_command(void);
char **tokenize_command(char *command);
int execute_command(char **args);

#endif /* SHELL_H */

