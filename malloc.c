#include <stdlib.h>
#include "main.h"

/**
 * _calloc - This fuction allocates memory using malloc
 * @nmemb: number of elements.
 * @size: size in bytes of each element.
 * Return: pointer to the espace reserved.
 *
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *array = NULL;
	unsigned int i;
	unsigned int t;
	char *f;

	if (size == 0 || nmemb == 0)
		return (NULL);
	t = nmemb * size;
	array = malloc(t);
	f = (char *)array;
	if (f != NULL)
	{
		for (i = 0; i < t; i++)
			f[i] = 0;
		return (f);
	}
	return (NULL);
}
