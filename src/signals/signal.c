#include "../../includes/minishell.h"

static void do_nothing()
{
	return ;
}

void	ft_signal(int code)
{
	if (code == SIGINT && !g_is_executed)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (code == SIGQUIT && !g_is_executed)
		do_nothing();
	if (g_is_executed)
		ft_putstr_fd("\n", 1);
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

int ctrl_d(t_minishell *shell, char *input)
{
	if (input == NULL)
	{
		on_eof(shell);
		return (TRUE);
	}
	return (FALSE);
}
