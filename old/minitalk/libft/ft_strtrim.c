#include "libft.h"

/*Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*tmp;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	tmp = (char *)s1;
	while (*tmp && ft_strchr(set, *tmp))
		tmp++;
	len = ft_strlen(tmp);
	while (len > 0 && ft_strchr(set, tmp[len]))
		len--;
	res = ft_substr(tmp, 0, len + 1);
	return (res);
}
