/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:39:14 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/12 00:17:57 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
if (exit_status >= 0) ?
shell->exit = TRUE;
*/
int	execute_builtin(t_minishell *shell, t_token *token)
{
	int	exit_status;

	if (ft_strcmp(token->str, "pwd") == 0)
		exit_status = ft_pwd();
	else if (ft_strcmp(token->str, "echo") == 0)
		exit_status = ft_echo(token->next);
	else if (ft_strcmp(token->str, "env") == 0)
		exit_status = ft_env();
	else if (ft_strcmp(token->str, "cd") == 0)
		exit_status = ft_cd(token->next);
	else if (ft_strcmp(token->str, "export") == 0)
		exit_status = ft_export(token->next);
	else if (ft_strcmp(token->str, "unset") == 0)
		exit_status = ft_unset(token->next);
	else if (ft_strcmp(token->str, "exit") == 0)
		exit_status = ft_exit(token->next, shell);
	else
	{
		ft_putstr_fd("minishell$: builtin error\n", 2);
		exit_status = -2;
	}
	g_is_tricky.g_ret = exit_status;
	return (exit_status);
}
