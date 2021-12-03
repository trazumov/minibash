#include "libft.h"

/*allocates enough space for count objects that are size bytes of memory each*/
void	*ft_calloc(size_t count, size_t size)
{
	char			*res;
	unsigned int	mem_bytes;
	unsigned int	i;

	mem_bytes = count * size;
	res = malloc(mem_bytes);
	if (!res)
		return (NULL);
	i = 0;
	while (mem_bytes)
	{
		res[i] = 0;
		i++;
		mem_bytes--;
	}
	return ((void *)res);
}
