#include "../includes/minishell.h"

int	open_file_error(t_minishell *shell)
{
	ft_putstr_fd(shell->message, STDERR);
	ft_putstr_fd(shell->tokens->str, STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	shell->ret = 1;
	return (-1);
}