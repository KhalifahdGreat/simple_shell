#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *command;
	int status;

	while (1)
	{
		prompt(); /* Display prompt */
		command = read_command(); /* Read user input */
		if (command == NULL) /* Handle EOF (Ctrl+D) */
		{
			printf("\n");
			break;
		}

		status = execute_command(command); /* Execute the command */
		free(command); /* Free the allocated memory */

		if (status == -1) /* If exit command, break the loop */
			break;
	}

	return (0);
}

/**
 * prompt - Display the shell prompt
 */
void prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * read_command - Read a command from the standard input
 *
 * Return: The command entered by the user
 */
char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin); /* Read input from the user */
	if (nread == -1)
	{
		free(line); /* Free memory if getline fails */
		return (NULL);
	}

	/* Remove newline character from the input */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - Execute the command using execve
 * @command: The command to execute
 *
 * Return: 0 on success, -1 if the command is "exit"
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2]; /* Create a fixed-size array of pointers */

	/* Handle the "exit" command */
	if (strcmp(command, "exit") == 0)
		return (-1);

	argv[0] = command;  /* Set the first element to the command */
	argv[1] = NULL;     /* The last element must be NULL */

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0) /* Child process */
	{
		/* Execute the command */
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for the child process to finish */
	}

	return (0);
}

