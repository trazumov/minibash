#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	rl_catch_signals = 0;
	shell->message = ft_strdup("minishell$ ");
	shell->signal_c = FALSE;
	shell->signal_q = FALSE;
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->ret = 0;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->save_history = TRUE;
}