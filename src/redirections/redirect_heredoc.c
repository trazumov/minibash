/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:47:20 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/16 19:55:14 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_heredoc_err(void)
{
	perror("here_doc error");
	exit(EXIT_FAILURE);
}

static int	create_tmp_file(t_token *token)
{
	int		in;
	char	*line;
	int		next_len;

	in = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (in < 0 || read(in, 0, 0) < 0)
		exit_heredoc_err();
	ft_putstr_fd("> ", 0);
	while (get_next_line(0, &line) & g_is_tricky.g_run)
	{
		next_len = ft_strlen(token->next->str);
		if (ft_strncmp(line, token->next->str, next_len + 1) == 0)
			break ;
		ft_putendl_fd(line, in);
		free(line);
		ft_putstr_fd("> ", 0);
	}
	if (*line == 0)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	if (g_is_tricky.g_run)
		free(line);
	close_fd_save(in);
	if (g_is_tricky.g_run)
		return (0);
	return (1);
}

static void	exec_heredoc_parent(\
t_minishell *shell, pid_t parent)
{
	waitpid(parent, &g_is_tricky.g_ret, 0);
	handle_return_value(&g_is_tricky.g_ret);
	if (g_is_tricky.g_ret == 0)
	{
		shell->fd_in = open("here_doc", O_RDONLY);
		if (shell->fd_in < 0 || read(shell->fd_in, 0, 0) < 0)
			void_shell_err(shell);
		else if (dup2(shell->fd_in, 0) == -1)
			void_shell_err(shell);
		close_fd_save(shell->fd_in);
	}
}

void	exec_here_doc(t_minishell *shell, t_token *token)
{
	pid_t	parent;

	parent = fork();
	if (parent == -1)
		return (void_shell_err(shell));
	if (parent)
		exec_heredoc_parent(shell, parent);
	else if (parent == 0)
	{
		signal(SIGINT, ft_signal_doc);
		signal(SIGQUIT, ft_signal_doc);
		if (dup2(shell->in, STDIN) == -1)
			return (void_shell_err(shell));
		close_fd_save(shell->in);
		if (create_tmp_file(token) == 0)
		{
			free_environ();
			exit (0);
		}
	}
}

/*
return 0 OK | return 1 ERR
*/
int	redirect_heredoc(t_minishell *shell, t_token *token, int *new_input)
{
	if ((*new_input) == TRUE)
	{
		get_prev_input(token)->skip = TRUE;
		close_fd_save(shell->fd_in);
	}
	if (token->next)
	{
		g_is_tricky.here_doc = TRUE;
		exec_here_doc(shell, token);
		g_is_tricky.here_doc = FALSE;
		(*new_input) = TRUE;
	}
	else
		return_shell_err(shell);
	return (0);
}
