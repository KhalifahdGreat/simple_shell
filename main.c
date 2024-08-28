#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("($) ");  /* Prompt */
		nread = getline(&line, &len, stdin);  /* Read user input */

		if (nread == -1)  /* Check for EOF or error */
		{
			free(line);
			break;
		}

		printf("%s", line);  /* Echo input for now */

		/* Additional code to handle commands will go here */
	}

	return (0);
}

