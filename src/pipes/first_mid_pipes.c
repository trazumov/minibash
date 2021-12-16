/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_mid_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:58:18 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/16 22:56:03 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns prev execv token or builtin token
*/
t_token	*get_prev_token(t_token *token)
{
	t_token	*res;

	if (token->prev == NULL)
		return (NULL);
	else if (token->prev->type == PIPE)
		return (token->prev);
	else
	{
		res = token->prev;
		while (res->prev && res->prev->type != PIPE)
			res = res->prev;
	}
	if (res->skip)
	{
		res = res->next;
		while (res->type > BUILTIN)
			res = res->next;
		if (res->prev && res->prev->type >= REDIR_OUT)
			res = res->next;
	}
	return (res);
}

static void	execute_child_mid(t_minishell *shell, t_token *token, int fd)
{
	if (!token_has_redir_in(shell, get_prev_token(token)))
	{
		if (dup2(shell->fds[fd - 1][0], STDIN) == -1)
			return (void_shell_err(shell));
		close_fd_save(shell->fds[fd - 1][1]);
	}
	if (shell->error)
		save_exit_child();
	if (!token_has_redir_out(shell, get_prev_token(token)))
	{
		if (dup2(shell->fds[fd][1], STDOUT) == -1)
			return (void_shell_err(shell));
		close_fd_save(shell->fds[fd][0]);
	}
	if (shell->error)
		save_exit_child();
	if (get_prev_token(token)->type <= ARG)
		execv_cmd(get_prev_token(token));
	else
	{
		g_is_tricky.g_ret = (execute_builtin(shell, get_prev_token(token)));
		free_environ();
		exit (g_is_tricky.g_ret);
	}
}

int	first_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		return_shell_err(shell);
	parent = fork();
	if (parent == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
		execute_child_first(shell, token, fd);
	return (0);
}

int	mid_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		return_shell_err(shell);
	parent = fork();
	if (parent == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
		execute_child_mid(shell, token, fd);
	close_fd_save(shell->fds[fd - 1][0]);
	close_fd_save(shell->fds[fd - 1][1]);
	return (0);
}
