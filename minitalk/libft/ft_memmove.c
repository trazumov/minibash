#include "libft.h"

/*copies len bytes from string src to string dst.  The two
     strings may overlap; the copy is always done 
	 in a non-destructive manner*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;
	unsigned int			i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (dest <= src)
	{
		while (n > 0)
		{
			d[i] = s[i];
			i++;
			n--;
		}
	}
	else
		while (n-- > 0)
			d[n] = s[n];
	return (dest);
}
