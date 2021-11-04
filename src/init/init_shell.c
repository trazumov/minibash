#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	rl_catch_signals = 0;
	shell->exit = FALSE;
	shell->message = ft_strdup("minishell> ");
}