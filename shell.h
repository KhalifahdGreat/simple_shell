#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Function Prototypes */
void prompt(void);
char *read_command(void);
int execute_command(char *command);

#endif /* SHELL_H */

