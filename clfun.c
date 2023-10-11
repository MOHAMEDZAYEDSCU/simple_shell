#include "main.h"
#include <stdio.h>
#define MAX 500

/**
 * getdir - Entry point
 *
 * Return: doble pointer to directories of the PATH
 */
char **getdir(void)
{
	int sp = 0, i = 0, l = 0, aux = 0, j = 0, flag = 1;
	int p = 0;
	char *path;
	char *var = "PATH";
	char **dir = NULL;

	path = _getenvvar(var);
	if (!path || path[0] == 0)
		return (NULL);
	sp = numdirectories(path);
	if (sp == 0)
		return (dir);
	dir = _calloc((sp + 1), sizeof(void *));
	dir[sp] = NULL;
	for (i = 0; i < sp; i++)
	{
		if (path[0] == ':' && flag)
		{
			dir[0] = currentpath();
			i++, j++;
			flag = 0; }
		aux = j;
		for (l = 0 ; path[j] && path[j] != ':'; j++, l++)
			;
		if (l == 0)
		{
			dir[i] = currentpath();
			j++;
			continue; }
		j++;
		dir[i] = _calloc(sizeof(char), (l + 2));
		for (p = 0; path[aux] && aux < 1024 && path[aux] != ':'; aux++, p++)
			*(dir[i] + p) = path[aux];
		*(dir[i] + p) = '/';
		p++;
		*(dir[i] + p) = 0;
		aux++;
		j = aux; }
	free(path);
	return (dir);
}

/**
 * freedir - verfy operators.
 * @dir: array of arrays with directories
 * @arg:array with argumens
 *
 * Return: no returns
 */
void freedir(char **dir, char *arg)
{
	int l = 0;

	if (arg)
		free(arg);
	for (l = 0; dir[l]; l++)
		free(dir[l]);
	free(dir[l]);
	free(dir);
}

/**
 * _strlen2 - Entry point
 *@s: pointer the string we want to now length
 *
 * Return: 0
 */
int _strlen2(char *s)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * current_dir - show help document of some functions.
 * @arg: node tha has the builtin command
 *
 * Return: no return
 */
int current_dir(char **arg)
{
	char *py = NULL;
	int pos = 0, i = 0, fd = 0;

	py = currentpath();
	pos = _strlen2(py);
	for (; arg[0][i]; i++)
		py[pos + i] = arg[0][i];
	fd = open(py, O_RDONLY);
	if (fd == -1)
	{
		free(py);
		return (-1);
	}
	free(arg[0]);
	arg[0] = py;
	close(fd);
	return (0);

}
/**
 * clfun - sort out command.
 * @arg: command with arguments
 *
 * Return: 1 if is built in or 0 if its external function
 */
int  clfun(char **arg)
{
	char *com = NULL, *crtdir = NULL, *aux = NULL;
	char **dir = NULL;
	unsigned int i = 0, l = 0, la = 0;
	int res, fd = 0, found = 1;

	res = look(*arg);
	if (res == BUILT)
		return (BUILT);
	com = *arg;
	if (arg[0][0] == '.' && arg[0][1])
		return (current_dir(arg));
	if (*(*(arg + 0) + 0) == '/')
		return (0);
	dir = getdir();
	if (dir == NULL)
		return (-1);
	la = _strlen2(com);
	la++;
	while (dir[i])
	{
		crtdir = dir[i];
		l = _strlen2(crtdir);
		aux = _calloc(sizeof(char), (la + l + 1));
		if (aux == NULL)
			return (0);
		aux = dirandcommand(crtdir, aux, com);
		fd = open(aux, O_RDONLY);
		if (fd != -1)
		{
			freedir(dir, *arg);
			*arg = aux;
			found = 0;
			close(fd);
			break; }
		i++;
		free(aux); }
	if (found)
	{
		freedir(dir, NULL);
		res = -1; }
	return (res); }
