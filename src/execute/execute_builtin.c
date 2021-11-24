#include "../../includes/minishell.h"

void	execute_builtin(t_token *token, char **envp)
{
	if (ft_strcmp(token->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(token->str, "echo") == 0)
		ft_echo(token);
	else if (ft_strcmp(token->str, "env") == 0)
		ft_env();
	else if (ft_strcmp(token->str, "cd") == 0)
		ft_cd(token->next);
	else if (ft_strcmp(token->str, "export") == 0)
		ft_export(token->next);
	else if (ft_strcmp(token->str, "unset") == 0)
		ft_unset(token);
	else if (ft_strcmp(token->str, "exit") == 0)
		ft_exit(token);
	else
	{
		printf("Builtin error\n");
	}
}