/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:18:32 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 17:56:25 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_new_heredoc(t_minishell *shell, t_token *token)
{
	close_fd_save(shell->fd_in);
	if (token->next->type == CMD || token->next->type == ARG)
		exec_here_doc(shell, token);
}

void	handle_new_in(t_minishell *shell, t_token *token)
{
	char	*file;

	close_fd_save(shell->fd_in);
	if (token->next->type == CMD || token->next->type == ARG)
	{
		file = token->next->str;
		shell->fd_in = open(file, O_RDONLY, S_IRWXU);
		if (shell->fd_in == -1)
		{
			shell->error = TRUE;
			perror(shell->message);
			return ;
		}
		dup2(shell->fd_in, STDIN);
	}
}

void	handle_new_out(t_minishell *shell, t_token *token)
{
	char	*file;

	close_fd_save(shell->fd_out);
	if (token->next->type == CMD || token->next->type == ARG)
	{
		file = token->next->str;
		if (token->type == REDIR_OUT)
			shell->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (token->type == REDIR_OUT_2)
			shell->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (shell->fd_out == -1)
		{
			shell->error = TRUE;
			perror(shell->message);
			return ;
		}
		dup2(shell->fd_out, STDOUT);
	}
}

int	token_has_redir_out(t_minishell *shell, t_token *token)
{
	t_token	*find_next;
	int		ret;

	ret = FALSE;
	find_next = token;
	while (find_next->prev && find_next->prev->type != PIPE)
		find_next = find_next->prev;
	while (find_next && find_next->type != PIPE)
	{
		if (find_next->type == REDIR_OUT || find_next->type == REDIR_OUT_2)
		{
			ret = TRUE;
			handle_new_out(shell, find_next);
		}
		find_next = find_next->next;
	}
	return (ret);
}

int	token_has_redir_in(t_minishell *shell, t_token *token)
{
	t_token	*find_next;
	int		ret;

	ret = FALSE;
	find_next = token;
	while (find_next->prev && find_next->prev->type != PIPE)
		find_next = find_next->prev;
	while (find_next && find_next->type != PIPE)
	{
		if (find_next->type == REDIR_IN)
		{
			ret = TRUE;
			handle_new_in(shell, find_next);
		}
		if (find_next->type == REDIR_HEREDOC)
		{
			ret = TRUE;
			handle_new_heredoc(shell, find_next);
		}
		find_next = find_next->next;
	}
	return (ret);
}
