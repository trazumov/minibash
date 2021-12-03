#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	while (s[len] != '\0')
		len++;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
