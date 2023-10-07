#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - Displays a prompt to the user.
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "", 0);
}

/**
 * execute_command - Executes a command with arguments.
 * @command: The command to execute.
 * @args: The arguments to pass to the command.
 */
void execute_command(char *command, char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		if (execve(command, args, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Fork failed");
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

/**
 * main - The main function.
 * Return: 0 on success, EXIT_FAILURE on failure.
 */
int main(void)
{
	char *input = NULL;
	size_t input_len = 0;

	while (1)
	{
		display_prompt();

		/* Read input from the user */
		if (getline(&input, &input_len, stdin) == -1)
		{
			/* End of file (Ctrl+D) */
			free(input);
			exit(EXIT_SUCCESS);
		}

		/* Remove the trailing newline character */
		input[strcspn(input, "\n")] = '\0';

		/* Tokenize input by spaces */
		char *token = strtok(input, " \t\n");
		char *args[MAX_COMMAND_LENGTH];
		int arg_index = 0;

		while (token != NULL)
		{
			args[arg_index] = token;
			arg_index++;
			token = strtok(NULL, " \t\n");
		}
		args[arg_index] = NULL;

		/* Execute the command with arguments */
		if (arg_index > 0)
		{
			execute_command(args[0], args);
		}
	}

	free(input);

	return 0;
}

