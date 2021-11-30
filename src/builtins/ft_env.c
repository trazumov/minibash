#include "../../includes/minishell.h"

int	ft_env(void)
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}
