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
 * _help - show help document of some functions.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
int _help(command_t *h)
{
	char **argseach = NULL;
	int i = 0, j = 0, entero = 0, l;
	char *args[] = {"cd", "env", "history", "exit", "alias", "help", "setenv",
			"unsetenv", NULL};
	char *filenames[] = {"h_cd.txt", "h_env.txt", "h_history.txt",
			     "h_exit.txt", "h_alias.txt", "h_help.txt",
			     "h_setenv.txt", "h_unsetenv.txt", NULL};
	int *posi = &i;
	char *pathandfile = NULL, *buffer = NULL, *filejusthelp = "justhelp.txt";

	argseach = h->args;
	pathandfile = _calloc(500, 1);
	buffer = getpath();
	for (l = 0; buffer[l]; l++)
		pathandfile[l] = buffer[l];
	if (argseach[1] == NULL)
	{
		justhelp(pathandfile, l, filejusthelp);
		return (0); }
	if (argseach[1][0] == 0)
		return (0);
	while (args[i] != NULL)
	{
		entero = 0;
		for (j = 0; args[i][j] != '\0'; j++)
		{
			if (argseach[1][j] - args[i][j] != 0)
			{
				entero = argseach[1][j] - args[i][j];
				break; }}
		if (entero == 0)
			printhelp_text(filenames, posi, pathandfile);
		i++;
	}
	return (0);
}
