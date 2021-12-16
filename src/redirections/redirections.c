/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:57:01 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/16 22:38:32 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_error(void)
{
	g_is_tricky.g_ret = 1;
	return (-1);
}

t_token	*get_prev_input(t_token *token)
{
	t_token	*res;

	res = token->prev;
	while (res && (res->type != REDIR_IN && res->type != REDIR_HEREDOC))
		res = res->prev;
	return (res);
}

/*
return 0 OK | return 1 ERR
*/
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
			return_shell_err(shell);
		else if (dup2(shell->fd_in, STDIN) == -1)
			return_shell_err(shell);
		(*new_input) = TRUE;
	}
	else
		return_shell_err(shell);
	return (0);
}

static int	is_error(t_minishell *shell)
{
	if (shell->error)
	{
		g_is_tricky.g_ret = 1;
		return (1);
	}
	return (0);
}

/*
return 0 OK | return -1 ERR
*/
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
		if (is_error(shell))
			break ;
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
			if (redirect_out(shell, token, &new_output))
				return (open_file_error());
		if (token->type == REDIR_IN)
			if (redirect_in(shell, token, &new_input))
				return (open_file_error());
		if (token->type == REDIR_HEREDOC)
			if (redirect_heredoc(shell, token, &new_input))
				return (open_file_error());
		if (g_is_tricky.g_run == FALSE)
			return (1);
		token = token->next;
	}
	return (0);
}
