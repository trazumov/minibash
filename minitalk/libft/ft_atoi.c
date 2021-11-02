#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c == ' ') || (c == '\n') || (c =='\t') || \
	(c == '\v') || (c == '\f') || (c == '\r'))
		return (1);
	return (0);
}

/*converts the initial portion of string to int*/
int	ft_atoi(const char *str)
{
	int				res;
	int				sign;
	unsigned char	*tmp;

	sign = 1;
	res = 0;
	tmp = (unsigned char *)str;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (*tmp == '-')
		sign = -1;
	if ((*tmp == '-') || (*tmp == '+'))
		tmp++;
	while (*tmp && *tmp >= '0' && *tmp <= '9')
	{
		res = res * 10 + (*tmp - 48);
		tmp++;
	}
	return (res * sign);
}
