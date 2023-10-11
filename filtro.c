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
 * getpath - get current path
 *
 * Return: no return
 */

char *getpath(void)
{

	static int flag;
	static char *path;

	if (!flag)
	{
		path = _calloc(500, 1);
		if (path == NULL)
			return (0);
		path = getcwd(path, 500);
		flag = 1;
	}
	return (path);
}

/**
 * lukeSkywalker - return 0.
 *
 * Return: no return
 */
int lukeSkywalker(void)
{
	return (0);
}

/**
 * aredots - filter (.. /).
 * @path: pointer to path
 * @pos: position in buffer to verify if it is . . and /
 * @size: size of buffer
 * Return: 0 or 1
 */
int aredots(char *path, int pos, int size)
{
	if (path[pos] && path[pos + 1] && path[pos + 2])
	{
		if (path[pos] == '/' && path[pos + 1] == '.'
		    && path[pos + 2] == '.')
		{
			if ((pos + 3) <= size)
			{
				if ((path[pos + 3]) == 0 ||
				    (path[pos + 3]) == '/')
					return (1);
			}
		}
	}
	return (0);
}

/**
 * filtro1 - delete extra /.
 * @path: pointer to path
 *
 * Return: no return
 */
char *filtro1(char *path)
{
	char *filter = NULL;
	int j = 0, seek = 0, i = 0;

	for (; path[j]; j++)
		;
	filter = _calloc(j + 1, sizeof(char));
	for (; path[i]; i++)
	{
		if (path[i] == '/')
		{
			if (path[i + 1] == 0)
				break;
			if ((i + 1 <= j) && path[i + 1] == '/')
				continue;
			filter[seek] = path[i];
			seek++;
		}
		else
		{
			filter[seek] = path[i];
			seek++;
		}
	}
	return (filter);
}

/**
 * filtro2 - if we have two points after directory .
 * @filter: pointer to the buffer
 *
 * Return: pointer to the copy path
 */
char *filtro2(char *filter)
{
	char *cpypath = NULL;
	int j = 0, pos = 0, i = 0, cnt = 0;

	for (; filter[j]; j++)
		;
	cpypath = _calloc(j + 1, sizeof(char));

	for (i = 0; i <= j && filter[i]; i++)
	{
		if (i == 0 && aredots(filter, i, j))
		{
			i += 2;
			continue;
		}
		pos = nextdir(filter, i);
		if (pos == -1)
		{
			for (; filter[i]; i++, cnt++)
				cpypath[cnt] = filter[i];
			break;
		}
		if (aredots(filter, pos, j))
		{
			i = pos + 2;
			continue;
		}
		for (; i <= pos && filter[i]; i++, cnt++)
			cpypath[cnt] = filter[i];
		i--;
	}
	return (cpypath);
}
