#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	res;
	unsigned int	i;
	int				len1;
	int				len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}