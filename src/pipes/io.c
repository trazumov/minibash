/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:08:44 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 16:09:23 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io_first(t_minishell *shell, t_token *token, int fd)
{
	token_has_redir_in(shell, token);
	if (!token_has_redir_out(shell, token))
		dup2(shell->fds[fd][1], STDOUT);
	close_fd_save(shell->fds[fd][0]);
}

void	set_io_last(t_minishell *shell, t_token *token, int fd)
{
	if (!token_has_redir_in(shell, token))
	{
		dup2(shell->fds[fd][0], STDIN);
		close_fd_save(shell->fds[fd][1]);
	}
	token_has_redir_out(shell, token);
}
