/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:16:50 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/16 22:58:26 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_first(t_minishell *shell, t_token *token, int fd)
{
	t_token	*execute_token;

	execute_token = get_prev_token(token);
	set_io_first(shell, execute_token, fd);
	if (shell->error)
		save_exit_child();
	if (execute_token->type == CMD || execute_token->type == ARG)
		execv_cmd(execute_token);
	else
	{
		g_is_tricky.g_ret = (execute_builtin(shell, execute_token));
		free_environ();
		exit (g_is_tricky.g_ret);
	}
}

static void	execute_child_left(t_minishell *shell, t_token *token, int fd)
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

void	execute_child_right(t_minishell *shell, t_token *token, int fd)
{
	t_token	*execute_token;

	execute_token = token->next;
	set_io_last(shell, execute_token, fd);
	if (shell->error)
		save_exit_child();
	if (execute_token->type == CMD || execute_token->type == ARG)
		execv_cmd(execute_token);
	else
	{
		g_is_tricky.g_ret = (execute_builtin(shell, execute_token));
		free_environ();
		exit (g_is_tricky.g_ret);
	}
}

int	last_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[fd]) != 0)
		return_shell_err(shell);
	parent = fork();
	if (parent == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
		execute_child_left(shell, token, fd);
	close_fd_save(shell->fds[fd - 1][0]);
	close_fd_save(shell->fds[fd - 1][1]);
	cmd = fork();
	if (cmd == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == 0)
		execute_child_right(shell, token, fd);
	close_fd_save(shell->fds[fd][0]);
	close_fd_save(shell->fds[fd][1]);
	return (0);
}

int	the_only_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[0]) == -1)
		return_shell_err(shell);
	parent = fork();
	if (parent == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
		execute_child_first(shell, token, fd);
	cmd = fork();
	if (cmd == -1)
		return_shell_err(shell);
	else
		struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == 0)
		execute_child_right(shell, token, fd);
	close_fd_save(shell->fds[0][0]);
	close_fd_save(shell->fds[0][1]);
	return (0);
}
