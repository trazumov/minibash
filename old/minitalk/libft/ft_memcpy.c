#include "libft.h"

/*copies n bytes from memory area src to memory area dst.  If
     dst and src overlap, behavior is undefined*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*from;
	unsigned int	i;

	res = (unsigned char *)dest;
	from = (unsigned char *)src;
	i = 0;
	while (n-- > 0)
	{
		res[i] = from[i];
		i++;
	}
	return (dest);
}
