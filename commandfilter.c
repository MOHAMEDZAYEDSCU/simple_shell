#include "main.h"

/**
 * _ignorecomments - ignorecomments.
 * @buf: node tha has the builtin command
 * @i: integer
 *
 * Return: no return
 */
void _ignorecomments(char *buf, int *i)
{
	while (buf[*i] != 0 && buf[*i] != '\n')
	{
		*i = *i + 1;
	}
	*i = *i + 1;
}

/**
 * _isalias - show help document of some functions.
 * @buf: node tha has the builtin command
 * @i: integer
 *
 * Return: no return
 */
alias *_isalias(char *buf, int *i)
{
	alias *ali =  NULL;
	int cb = *i, j = 0;
	char *name = NULL;

	if (cb != 0 && !_isespecialchr(buf[(cb - 1)]))
		return (NULL);
	name = _calloc(500, 1);
	for (; !_isespecialchr(buf[cb]); cb++)
		;
	for (; (j + *i) < cb; j++)
		name[j] = buf[j + *i];
	ali = setalias(NULL);
	ali = buscar_alias(ali, name);
	free(name);
	if (ali)
	{
		*i = cb;
		return (ali);
	}
	return (NULL);
}

/**
 * _replacealias - show help document of some functions.
 * @ali: node tha has the builtin command
 * @newbuf: new buffer
 * @pos: size all line
 *
 * Return: no return
 */
void _replacealias(alias *ali, char *newbuf, int *pos)
{
	int i = 0;
	char *value = NULL;
	alias *aux = NULL;

	aux = setalias(NULL);
	aux = buscar_alias(aux, ali->value);
	if (aux)
		ali = aux;
	value = ali->value;
	while (value[i])
	{
		if (value[i] != 39)
		{
			newbuf[*pos] = value[i];
			*pos = *pos + 1;
		}
		i++;
	}
}

/**
 * buffer_filter - show help document of some functions.
 * @buffer: node tha has the builtin command
 * @p: p
 *
 * Return: no return
 */
void buffer_filter(char **buffer, ssize_t *p)
{
	char *newbuf = _calloc(4096 * 2, 1);
	alias *ali = NULL;
	char *buf = *buffer;
	int pos = 0, i = 0, cpy = 0;

	while (i <= *p)
	{
		if (buf[i] == '#')
		{
			if (i == 0)
			{
				_ignorecomments(buf, &i);
				continue; }
			else if (buf[i - 1] == ' ' || buf[i - 1] == '\t' ||
				 buf[i - 1] == ';')
			{
				_ignorecomments(buf, &i);
				continue; }
		}
		if (buf[i] == '$' && buf[i + 1] != ' ' && buf[i + 1] != '\t'
			    && buf[i + 1] != 0 && buf[i + 1] != '\n'
		    && buf[i + 1] != ';')
		{
			_replacevar(buf, newbuf, &i, &pos);
			continue; }
		cpy = i;
		ali = _isalias(buf, &i);
		if (ali)
		{
			if (!have_alias(buf, i))
			{
				_replacealias(ali, newbuf, &pos);
				continue; }
			i = cpy; }
		i = cpy;
		newbuf[pos] = buf[i];
		i++, pos++; }
	free(buf);
	*p = pos;
	*buffer = newbuf;
}
