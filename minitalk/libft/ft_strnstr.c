#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	src;
	size_t	n;

	if (*needle == '\0')
		return ((char *)haystack);
	src = 0;
	n = ft_strlen(needle);
	while (haystack[src] != '\0' && len > 0)
	{
		if (ft_strncmp(&haystack[src], &needle[0], n) == 0)
			if (len >= n)
				return ((char *)(&haystack[src]));
		src++;
		len--;
	}
	return (NULL);
}
