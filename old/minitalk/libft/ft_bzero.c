#include "libft.h"

/*writes n zeroed bytes to the string s*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
