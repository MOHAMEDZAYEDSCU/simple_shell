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
 * getvaderdir - get variable directory.
 *
 * Return: no return
 */
char  *getvaderdir(void)
{
	int l = 0, i = 0;
	char *pwd = NULL;
	char *newpwd = NULL;

	pwd = _getenvvar("PWD");
	for (; pwd[l]; l++)
		if (pwd[l] == '/')
			i = l;
	newpwd = _calloc(i + 2, sizeof(char));
	for (l = 0; pwd[l] && l < i; l++)
		newpwd[l] = pwd[l];
	free(pwd);
	return (newpwd);
}

/**
 * chtopreviousdir - give previous directory.
 *
 * Return: no return
 */
int chtopreviousdir(void)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
	int l = 0;
	char sl = '\n';

	oldpwd = _getenvvar("OLDPWD");
	pwd = _getenvvar("PWD");
	if (!oldpwd)
	{
		printf("OLDPWD not set error");
		free(pwd);
		return (-1);
	}
	else
	{
		dir = opendir(oldpwd);
		if (dir == NULL)
		{
			printf("ERROR\n");
			return (-1);
		}
		closedir(dir);
		chdir(oldpwd);
		_setenv("OLDPWD", pwd);
		for (; oldpwd[l]; l++)
			;
		write(1, oldpwd, l);
		write(1, &sl, 1);
		free(pwd);
		free(oldpwd);
		return (0);
	}
	return (-1);
}

/**
 * darthVader - change directory father.
 *
 * Return: return 0
 */
int darthVader(void)
{
	char *newpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;

	pwd = _getenvvar("PWD");
	newpwd = getvaderdir();
	dir = opendir(newpwd);
	if (dir == NULL)
	{
		printf("Error :'v \n");
		free(pwd);
		free(newpwd);
		return (-1);
	}
	closedir(dir);
	chdir(newpwd);
	_setenv("PWD", newpwd);
	_setenv("OLDPWD", pwd);
	free(pwd);
	free(newpwd);
	return (0);
}

/**
 * nextdir - give next dire after .. /.
 * @filter: pointer to buffer
 * @i: position before directory
 * Return: position of the next dir or -1
 */
int nextdir(char *filter, int i)
{
	if (!filter[i])
		return (-1);
	i++;
	for (; filter[i]; i++)
		if (filter[i] == '/')
			return (i);
	return (-1);
}

/**
 * dirandcommand - add command to the directory of the path.
 * @crtdir: each directory
 * @aux: pointer to the filename
 * @com: command and arguments
 *
 * Return: pointer to the etotal path of the directory
 */
char *dirandcommand(char *crtdir, char *aux, char *com)
{

	int l, la;

	for (l = 0; crtdir[l]; l++)
		aux[l] = crtdir[l];
	for (la = 0; com[la]; la++, l++)
		aux[l] = com[la];
	aux[l] = 0;
	return (aux);
}
