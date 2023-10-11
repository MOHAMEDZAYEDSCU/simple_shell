#include "main.h"

/**
 * print_all_alias - show help document of some functions.
 *
 * Return: no return
 */
void print_all_alias(void)
{
	alias *aux = NULL;

	aux = setalias(NULL);
	while (aux)
	{
		print_one_alias(aux->name);
		aux = aux->next;
	}
}

/**
 * _alias - show help document of some functions.
 * @h: node tha has the builtin command
 *
 * Return: 0 or -1
 */
int _alias(command_t *h)
{
	char **args = NULL;
	char **tokens = NULL;
	int pos = 1, i = 0;

	args = h->args;
	for  (; args[i]; i++)
		;
	if (i == 1)
	{
		print_all_alias();
		return (0);
	}
	while (pos < i)
	{
		if (_have_value(args[pos]))
		{
			tokens = token_alias(args[pos]);
			setalias(tokens);
			free(tokens);
		}
		else
			print_one_alias(args[pos]);
		pos++;
	}
	return (0);
}
