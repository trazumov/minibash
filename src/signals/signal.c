#include "../../includes/minishell.h"

void	ft_signal(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal = 1;
	}
	// заменить пустым выполнением
	if (code == SIGQUIT)
	{
		ft_putstr_fd("SIGQUIT\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal = 1;
	}
}

/*
Обработка нажатия Ctrl + D что по сути является вызовом EOF
*/
void	on_eof(t_minishell *shell)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("exit\n", 1);
	shell->exit = TRUE;
}