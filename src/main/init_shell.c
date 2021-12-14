/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:35:49 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/14 21:41:48 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->message = ft_strdup("minishell$ ");
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	if (!shell->in)
		return (void_shell_err(shell));
	shell->out = dup(STDOUT);
	if (!shell->out)
		return (void_shell_err(shell));
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->childs = NULL;
	shell->error = FALSE;
}
