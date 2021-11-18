#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	rl_catch_signals = 0; // перехват сигналов для обработки SIGIN SIGQUIT
	shell->exit = FALSE; // переменная используется для выхода из главного цикла
	shell->in = dup(STDIN); // сохраняем чтобы потом восстановить
	shell->out = dup(STDOUT); // сохраняем чтобы потом восстановить
	shell->pipin = -1;
	shell->pipout = -1;
	shell->pid = -1;
	shell->parent = TRUE;
}