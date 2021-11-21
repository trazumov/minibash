#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	rl_catch_signals = 0; // перехват сигналов для обработки SIGIN SIGQUIT
	shell->message = ft_strdup("minishell$ ");
	shell->exit = FALSE; // переменная используется для выхода из главного цикла
	shell->in = dup(STDIN); // сохраняем чтобы потом восстановить
	shell->out = dup(STDOUT); // сохраняем чтобы потом восстановить
	shell->ret = 0; // значение которое возвращает shell
	shell->fd_in = -1; // redir
	shell->fd_out = -1; // redir
	//shell->is_redir = FALSE;
}