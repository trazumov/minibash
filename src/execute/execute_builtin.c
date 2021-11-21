#include "../../includes/minishell.h"

int execute_builtin(t_token *token, char **envp)
{
	if (ft_strcmp(token->str, "pwd"))
		return (ft_pwd());
	if (ft_strcmp(token->str, "echo"))
		return (ft_echo(token));
	else
		return (1);
}