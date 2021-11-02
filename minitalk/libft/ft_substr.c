#include "libft.h"

static unsigned int	get_max_mem(char const *s, size_t len)
{
	unsigned int	strlen;

	strlen = ft_strlen(s);
	if (strlen < len)
		return (strlen);
	else
		return (len);
}

/*Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’
NULL if the allocation fails*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	res = (char *)malloc(get_max_mem(s, len) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while ((i != start) && (s[i] != '\0'))
		i++;
	while ((len-- > 0) && (s[i] != '\0'))
		res[j++] = s[i++];
	res[j] = '\0';
	if (j >= 0)
		return (res);
	else
	{
		free(res);
		return (NULL);
	}
}
