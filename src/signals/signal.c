#include "../../includes/minishell.h"

void	ft_signal(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("SIGINT\n", 1);
		g_signal = 1;
	}
}