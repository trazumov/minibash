/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:47:08 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 19:50:05 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_prev_redir(t_token *token)
{
	t_token	*res;

	res = token->prev;
	while (res && res->type != REDIR_OUT_2 && res->type != REDIR_OUT)
		res = res->prev;
	return (res);
}

static void	handle_new_ouput(t_minishell *shell, t_token *token)
{
	get_prev_redir(token)->skip = TRUE;
	close_fd_save(shell->fd_out);
}

/*
return 0 if OK ; return 1 if ERROR
O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU
*/
int	redirect_out(t_minishell *shell, t_token *token, int *new_output)
{
	if (*new_output)
		handle_new_ouput(shell, token);
	if (token->next)
	{
		if (token->type == REDIR_OUT)
			shell->fd_out = open(token->next->str, \
			O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (token->type == REDIR_OUT_2)
			shell->fd_out = open(token->next->str, \
			O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (shell->fd_out == -1)
		{
			shell->error = TRUE;
			perror("minishell");
			return (1);
		}
		dup2(shell->fd_out, STDOUT);
		(*new_output) = TRUE;
	}
	else
		shell->fd_out = -1;
	if (!shell->fd_out)
		return (1);
	return (0);
}
