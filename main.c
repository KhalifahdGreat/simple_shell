#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *command;
	char **args;
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

		args = tokenize_command(command); /* Tokenize the input */
		if (args[0] == NULL) /* No command entered */
		{
			free(command);
			free(args);
			continue;
		}

		status = execute_command(args); /* Execute the command */

		free(command); /* Free the allocated memory */
		free(args);    /* Free the tokenized arguments */

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
 * tokenize_command - Tokenizes the command string into arguments
 * @command: The command string to tokenize
 *
 * Return: An array of strings (tokens)
 */
char **tokenize_command(char *command)
{
	int bufsize = MAX_TOKENS, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += MAX_TOKENS;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL; /* Null-terminate the array */

	return (tokens);
}

/**
 * execute_command - Execute the command using execve
 * @args: The array of arguments (tokens)
 *
 * Return: 0 on success, -1 if the command is "exit"
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	/* Handle the "exit" command */
	if (strcmp(args[0], "exit") == 0)
		return (-1);

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0) /* Child process */
	{
		/* Execute the command */
		if (execve(args[0], args, NULL) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for the child process to finish */
	}

	return (0);
}

