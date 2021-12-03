#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	res;
	unsigned int	i;

	i = 0;
	res = 0;
	while (n > 0)
	{
		if (s1[i] != s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			break ;
		}
		i++;
		n--;
	}
	return (res);
}
