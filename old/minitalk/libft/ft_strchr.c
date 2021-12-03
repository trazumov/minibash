#include "libft.h"

/*locates the first occurrence of c in s and locate \0*/
/*
char	*ft_strchr(const char *s, int c)
{
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)s;
	while (*res != (char)c)
	{
		if (*res == '\0')
			return (NULL);
		res++;
	}
	return (res);
}
*/
char	*ft_strchr(const char *s, int c)
{
	char			*res;
	unsigned int	i;

	res = (char *)s;
	i = 0;
	while (res[i] != (char)c)
	{
		if (res[i] == '\0')
			return (NULL);
		i++;
	}
	return (&res[i]);
}
