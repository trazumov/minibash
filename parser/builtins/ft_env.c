#include "../parser.h"

void	ft_env(void)
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		printf("%s\n", __environ[i]);
		i++;
	}
}
