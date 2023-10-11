#include "main.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * imprimir_error - print error when command not found.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
void imprimir_error(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *n = NULL;
	char *cont = NULL;
	char *com = NULL;
	char *msg = ": not found";
	char sl = '\n';
	int a = 127;

	com = h->args[0];
	cont = print_number(h->cont);
	n = h->name;
	l1 = _strlen(n);
	write(STDERR_FILENO, n, l1 - 1);
	write(STDERR_FILENO, sp, 2);
	l1 = _strlen(cont);
	write(STDERR_FILENO, cont, l1 - 1);
	write(STDERR_FILENO, sp, 2);
	l1 = _strlen(com);
	write(STDERR_FILENO, com, l1 - 1);
	l1 = _strlen(msg);
	write(STDERR_FILENO, msg, l1 - 1);
	write(STDERR_FILENO, &sl, 1);
	free(cont);
	setstatus(&a);
}
