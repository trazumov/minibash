#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->message = ft_strdup("minishell$ ");
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->wait_s = 0;
	shell->save_history = TRUE;
	shell->childs = NULL;
	shell->error = FALSE;
}
