#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i] != '\0' & n-- > 0)
	{
		dest[i] = src[i];
		i++;
	}
	while (n-- > 0)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
