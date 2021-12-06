/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_mid_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:58:18 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/06 20:02:13 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		ft_putstr_fd("Pipe error\n", 2);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (parent == 0)
	{
		dup2(shell->fds[fd][1], STDOUT);
		close(shell->fds[fd][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
}

void	mid_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		ft_putstr_fd("Pipe error\n", 2);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (parent == 0)
	{
		dup2(shell->fds[fd - 1][0], STDIN);
		close(shell->fds[fd - 1][1]);
		dup2(shell->fds[fd][1], STDOUT);
		close(shell->fds[fd][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
	close(shell->fds[fd - 1][0]);
	close(shell->fds[fd - 1][1]);
}
