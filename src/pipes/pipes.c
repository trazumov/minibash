/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:16:50 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/06 21:50:01 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_left(t_minishell *shell, t_token *token, int fd)
{
	dup2(shell->fds[fd - 1][0], STDIN);
	close_fd_save(shell->fds[fd - 1][1]);
	dup2(shell->fds[fd][1], STDOUT);
	close_fd_save(shell->fds[fd][0]);
	if (get_prev_token(token)->type == CMD)
		execv_cmd(shell, get_prev_token(token));
	else
	{
		shell->ret = (execute_builtin(shell, get_prev_token(token)));
		exit (shell->ret);
	}
}

static void	execute_child_right(t_minishell *shell, t_token *token, int fd)
{
	dup2(shell->fds[fd][0], STDIN);
	close_fd_save(shell->fds[fd][1]);
	if (token->next->type == CMD)
		execv_cmd(shell, token->next);
	else
	{
		shell->ret = (execute_builtin(shell, token->next));
		exit (shell->ret);
	}
}

void	last_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[fd]) != 0)
		perror(shell->message);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		perror(shell->message);
	if (parent == 0)
		execute_child_left(shell, token, fd);
	close_fd_save(shell->fds[fd - 1][0]);
	close_fd_save(shell->fds[fd - 1][1]);
	cmd = fork();
	struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == -1)
		perror(shell->message);
	if (cmd == 0)
		execute_child_right(shell, token, fd);
	close_fd_save(shell->fds[fd][0]);
	close_fd_save(shell->fds[fd][1]);
}

void	the_only_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[0]) == -1)
		perror(shell->message);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
	{
		dup2(shell->fds[0][1], STDOUT);
		close_fd_save(shell->fds[0][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
	cmd = fork();
	struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == 0)
		execute_child_right(shell, token, fd);
	close_fd_save(shell->fds[0][0]);
	close_fd_save(shell->fds[0][1]);
}
