/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:57:01 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/11 22:42:38 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_prev_input(t_token *token)
{
	t_token	*res;

	res = token->prev;
	while (res && (res->type != REDIR_IN && res->type != REDIR_HEREDOC))
		res = res->prev;
	return (res);
}

static int	redirect_in(t_minishell *shell, t_token *token, int *new_input)
{
	if ((*new_input) == TRUE)
	{
		get_prev_input(token)->skip = TRUE;
		close_fd_save(shell->fd_in);
	}
	if (token->next)
	{
		shell->fd_in = open(token->next->str, O_RDONLY, S_IRWXU);
		if (shell->fd_in == -1)
		{
			shell->error = TRUE;
			perror("minishell");
			return (1);
		}
		if (dup2(shell->fd_in, STDIN) == -1)
			perror("minishell");
		(*new_input) = TRUE;
	}
	else
		(*new_input) = -1;
	if (!(*new_input))
		return (1);
	return (0);
}

int	set_redirection(t_minishell *shell)
{
	t_token	*token;
	int		new_input;
	int		new_output;

	new_output = FALSE;
	new_input = FALSE;
	token = shell->tokens;
	while (token)
	{
		if (shell->error)
			break ;
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
			if (redirect_out(shell, token, &new_output))
				return (open_file_error(shell));
		if (token->type == REDIR_IN)
			if (redirect_in(shell, token, &new_input))
				return (open_file_error(shell));
		if (token->type == REDIR_HEREDOC)
			if (redirect_heredoc(shell, token, &new_input))
				return (open_file_error(shell));
		token = token->next;
	}
	return (0);
}
