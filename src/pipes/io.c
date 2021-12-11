/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:08:44 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/11 23:50:57 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_io_first(t_minishell *shell, t_token *token, int fd)
{
	token_has_redir_in(shell, token);
	if (!token_has_redir_out(shell, token))
		if (dup2(shell->fds[fd][1], STDOUT) == -1)
			perror("minishell");
	close_fd_save(shell->fds[fd][0]);
}

void	set_io_last(t_minishell *shell, t_token *token, int fd)
{
	if (!token_has_redir_in(shell, token))
	{
		if (dup2(shell->fds[fd][0], STDIN) == -1)
			perror("minishell");
		close_fd_save(shell->fds[fd][1]);
	}
	token_has_redir_out(shell, token);
}
