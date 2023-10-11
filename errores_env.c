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
 * imprimir_error_env - print errors env builtin.
 * @h: the list of elements
 *
 * Return: direction of the new node
 */
void imprimir_error_env(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *filename = NULL;
	char *msg = ": No such file or directory";
	char sl = '\n';
	int a = 127;

	com = h->args[0];
	filename = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(filename);
	write(1, filename, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}
/**
 * search_file_env - search file name.
 * @h: the list of elements
 *
 * Return: o or -1 if it fails
 */
int search_file_env(command_t *h)
{

	char **filename = NULL;
	int n = 0;
	struct stat buf;

	filename = h->args;
	n = stat(filename[1], &buf);
	printf("%d", n);
	if (n == -1)
		imprimir_error_env(h);
	return (0);
}

/**
 * imprimir_error_setenv - print error setenv
 * @h: the list of elements
 *
 * Return: no return
 */
void imprimir_error_setenv(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *variable = NULL;
	char *msg = ": Variable not found";
	char sl = '\n';
	int a = 1;

	com = h->args[0];
	variable = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(variable);
	write(1, variable, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}

/**
 * imprimir_error_unsetenv - print unsetenv errors
 * @h: pointer ti the head of the linked list
 *
 * Return: no return
 */
void imprimir_error_unsetenv(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *variable = NULL;
	char *msg = ": Variable not found";
	char sl = '\n';
	int a = 1;

	com = h->args[0];
	variable = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(variable);
	write(1, variable, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}
