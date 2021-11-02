#include "libft.h"

/*The memccpy() function copies bytes from string 
src to string dst. If the character c 
(as converted to an unsigned char) occurs in the string src, 
the copy stops and a pointer to the byte after the 
copy of c in the string dst is returned.
Otherwise, n bytes are copied, and a NULL pointer is returned.*/
void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*res;
	unsigned char	*from;
	int				found;
	unsigned int	i;

	res = (unsigned char *)dest;
	from = (unsigned char *)src;
	found = 0;
	i = 0;
	while (n-- > 0)
	{
		res[i] = from[i];
		if (from[i] == (unsigned char)c)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 1)
		return (&res[i + 1]);
	else
		return (NULL);
}
