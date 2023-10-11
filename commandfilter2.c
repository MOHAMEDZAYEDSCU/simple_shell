#include "main.h"

/**
 * _isespecialchr - show help document of some functions.
 * @c: node tha has the builtin command
 *
 * Return: no return
 */
int _isespecialchr(char c)
{
	int i = 0;
	char tokens[] = {'&', '|', '\0', ';', '\n', '#', '$', ' ', '\t',  -1};

	while (tokens[i] != -1)
	{
		if (tokens[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * have_alias - show help document of some functions.
 * @buf: node tha has the builtin command
 * @i: int
 *
 * Return: no return
 */
int have_alias(char *buf, int i)
{
	int st = i - 1;
	int end = i;
	int cnt = 0, flag = 0;
	char *al = "alias";

	if (st < 0)
		return (0);
	while (st >= 0)
	{
		if (buf[st] == '\n' || buf[st] == 0
			   || buf[st] == ';' || buf[st] == '&'
		    || buf[st] == '|')
			break;
		st--;
	}
	if (st < 0)
		st++;
	for (; st <= end; st++)
	{
		if (buf[st] == 'a')
		{
			for (cnt = 0; al[cnt]; cnt++, st++)
			{
				if (al[cnt] != buf[st])
					break;
				if (!al[cnt + 1] && (buf[st + 1] == ' ' ||
						     buf[st + 1] == '\t'
						     || buf[st + 1] == '$'))
					flag = 1;
			}
		}
	}
	return (flag);
}

/**
 * replace_stat - show help document of some functions.
 * @buf: node tha has the builtin command
 * @newbuf: newbuf
 * @i: int
 * @pos: pos size
 *
 * Return: no return
 */
int replace_stat(char *buf, char *newbuf, int *i, int *pos)
{
	int a, j, p;
	char *stat;

	(void)buf;
	(void)i;
	a = 0, j = 0;
	a = setstatus(NULL);
	stat = print_number(a);
	p = *pos;
	for (; stat[j]; j++, p = p + 1)
		newbuf[p] = stat[j];
	p = p + 1;
	free(stat);
	return (p);
}

/**
 * replace_pid - show help document of some functions.
 * @buf: node tha has the builtin command
 * @newbuf: newbuffer
 * @i: int i
 * @pos: pos position
 *
 * Return: no return
 */
int replace_pid(char *buf, char *newbuf, int *i, int *pos)
{
	int a = setpid(NULL);
	char *stat = print_number(a);
	int j = 0;
	int p;

	(void)buf;
	(void)i;
	p = *pos;
	for (; stat[j]; j++, p++)
		newbuf[p] = stat[j];
	p++;
	free(stat);
	return (p);
}

/**
 * _replacevar - show help document of some functions.
 * @buf: node tha has the builtin command
 * @newbuf: newbuf
 * @i: int i
 * @pos: pos position
 *
 * Return: no return
 */
void _replacevar(char *buf, char *newbuf, int *i, int *pos)
{
	char *name = _calloc(60, 1);
	char *value = NULL;
	int cb = *i, j = 0, p = 0;

	cb++;
	if (buf[cb] == '$' || buf[cb] == '?')
	{
		if (buf[cb] == '$')
			p = replace_pid(buf, newbuf, i, pos);
		else
			p = replace_stat(buf, newbuf, i, pos);
		cb++;
		*i = cb;
		*pos = p - 1;
		return;
	}
	else
	{
		for (; !_isespecialchr(buf[cb]); cb++)
			;
		for (; (j + 1 + *i) < cb; j++)
			name[j] = buf[j + *i + 1];
	}
	value = _getenvvar(name);
	if (value)
	{
		for (j = 0; value[j]; j++, *pos = *pos + 1)
			newbuf[*pos] = value[j];
		free(value);
	}
	free(name);
	*i = cb;
}
