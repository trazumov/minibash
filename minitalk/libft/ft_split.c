#include "libft.h"

static unsigned int	count_substrs(char const *s, char c)
{
	unsigned int	res;
	char			*tmp;

	res = 0;
	tmp = (char *)s;
	while (*tmp != '\0')
	{
		if (*tmp != c)
		{
			res++;
			while (*tmp != c && *tmp != '\0')
				tmp++;
			while (*tmp == c && *tmp != '\0')
				tmp++;
		}
		else
			tmp++;
	}
	return (res + 1);
}

static unsigned int	get_pos_start(const char *s, unsigned int pos, char c)
{
	unsigned int	i;

	i = pos;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static unsigned int	get_pos_end(const char *s, unsigned int pos, char c)
{
	unsigned int	i;

	i = pos;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter.  The array must be
ended by a NULL pointer.
The array of new strings resulting from the split.
NULL if the allocation fails*/
char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	current;
	unsigned int	pos_end;
	unsigned int	pos_start;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * count_substrs(s, c));
	if (!res)
		return (NULL);
	pos_end = 0;
	pos_start = 0;
	current = 0;
	while (current < count_substrs(s, c) - 1)
	{
		pos_start = get_pos_start(s, pos_start, c);
		pos_end = get_pos_end(s, pos_start, c);
		if (pos_start != pos_end)
			res[current] = ft_substr(s, pos_start, pos_end - pos_start);
		pos_start = pos_end;
		current++;
	}
	res[current] = NULL;
	return (res);
}
