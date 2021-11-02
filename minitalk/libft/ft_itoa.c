#include "libft.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

static int	get_len(int n)
{
	unsigned int	res;
	long long	 	l;

	res = 0;
	l = n;
	if ((l > MAX_INT) || (l < MIN_INT))
		return (0);
	if (n < 0 && n >= -MAX_INT)
	{
		res++;
		n = -n;
	}
	if (n == MIN_INT)
		return (11);
	else
	{
		while (n >= 10)
		{
			res++;
			n = n / 10;
		}
	}
	return (res + 1);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = get_len(n);
	if (len == 0)
		return (NULL);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if (n == MIN_INT)
		return (ft_memcpy(res, "-2147483648", 12));
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[len--] = '\0';
	while (n >= 10)
	{
		res[len] = ((n % 10) + '0');
		len--;
		n = n / 10;
	}
	res[len] = ((n % 10) + '0');
	return (res);
}
