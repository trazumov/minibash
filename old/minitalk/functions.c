#include "minitalk.h"

char	*ft_strjoin_char(char *str, char c)
{
	char			*res;
	unsigned int	i;

	if (str == NULL)
	{
		res = (char *)malloc(2);
		if (!res)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	res = (char *)malloc(ft_strlen(str) + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[++i] = '\0';
	free(str);
	return (res);
}

int	decode_char(char bin[9])
{
	int	decimal;
	int	i;
	int	power;
	int	digit;

	decimal = 0;
	i = 0;
	power = 128;
	while (bin[i] != '\0')
	{
		if (bin[i] == '0')
			digit = 0;
		else
			digit = 1;
		decimal += power * digit;
		power /= 2;
		i++;
	}
	return (decimal);
}
