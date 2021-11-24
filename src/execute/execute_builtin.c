#include "../../includes/minishell.h"

void	execute_builtin(t_minishell *shell, t_token *token)
{
	int	exit_status;

	if (ft_strcmp(token->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(token->str, "echo") == 0)
		ft_echo(token->next);
	else if (ft_strcmp(token->str, "env") == 0)
		ft_env();
	else if (ft_strcmp(token->str, "cd") == 0)
		ft_cd(token->next);
	else if (ft_strcmp(token->str, "export") == 0)
		ft_export(token->next);
	else if (ft_strcmp(token->str, "unset") == 0)
		ft_unset(token->next);
	else if (ft_strcmp(token->str, "exit") == 0)
	{
		exit_status = ft_exit(token->next);
		if (exit_status >= 0)
			shell->exit = TRUE;
	}
	else
		printf("Builtin error\n");
}