#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t		res;

	res = 0;
	while (s[res] != '\0')
		res++;
	return (res);
}
