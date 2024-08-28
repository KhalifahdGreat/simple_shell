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
	printf(":) ");
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
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL; /* Null-terminate the array */

	return (tokens);
}

/**
 * find_command_path - Search for a command in the PATH
 * @command: The command to search for
 *
 * Return: The full path of the command if found, NULL otherwise
 */
char *find_command_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir;
	char *full_path = malloc(1024);

	if (strchr(command, '/') != NULL)
		return (command);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(full_path);
	free(path_copy);
	return (NULL);
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
	char *command_path;

	/* Handle the "exit" command */
	if (strcmp(args[0], "exit") == 0)
		return (-1);

	/* Find the command path */
	command_path = find_command_path(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0) /* Child process */
	{
		/* Execute the command */
		if (execve(command_path, args, NULL) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for the child process to finish */
	}

	if (command_path != args[0])
		free(command_path);

	return (0);
}

