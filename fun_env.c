#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX 500

/**
 * _env - show all environment variables.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
int _env(command_t *h)
{
	char **env = NULL, **args = NULL;
	int i = 0, l = 0;
	char sl = '\n';

	(void)h;
	args = h->args;
	if (args[1] != NULL)
	{
		search_file_env(h);
		return (0);
	}
	env = _setenv(NULL, NULL);
	while (env[i])
	{
		for (l = 0; env[i][l]; l++)
			;
		write(1, env[i], l);
		write(1, &sl, 1);
		i++;
	}
	return (0);
}

/**
 * _setenviron - set environ.
 * @h: node tha has the builtin command
 *
 * Return: o if succes or -1
 */
int _setenviron(command_t *h)
{
	char **args = NULL;
	int i = 0, st = 0;

	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 3)
	{
		setstatus(&st);
		return (0);
	}
	_setenv(args[1], args[2]);
	setstatus(&st);
	return (0);
}

/**
 * _unsetenv - unset variable.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
int _unsetenv(command_t *h)
{
	char **args = NULL;
	char *var = NULL;
	char *err = "Error\n";
	int i = 0;

	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 2)
	{
		write(STDERR_FILENO, err, _strlen(err));
		return (-1);
	}
	var = _getenvvar(args[1]);
	if (var)
	{
		_setenv(args[1], NULL);
		free(var);
		return (0);
	}
	else
	{
		write(STDERR_FILENO, err, _strlen(err));
		return (-1);
	}
	return (-1);
}
