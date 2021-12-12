/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:44:27 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/12 21:59:01 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// для введенного токена ищет следующий
static t_token	*get_next_token(t_token *token)
{
	t_token	*res;
	int		next_type;

	res = token->next;
	if (token->next == NULL)
		return (NULL);
	next_type = token->next->type;
	if (next_type == PIPE || next_type == REDIR_OUT || next_type == REDIR_OUT_2)
		return (token->next);
	if (token->type == PIPE)
		return (token->next);
	if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
		res = token->next;
	if ((next_type == CMD || next_type == ARG) && token->type != REDIR_IN)
	{
		res = token->next;
		while (res && (res->type == CMD || res->type == ARG))
			res = res->next;
	}
	if (token->type == REDIR_IN)
		res = token->next->next;
	return (res);
}

static int	have_to_wait(t_minishell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type == PIPE)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static void	wait_forks(t_minishell *shell)
{
	t_pid_t	*tmp;

	if (!have_to_wait(shell))
		return ;
	tmp = shell->childs;
	while (tmp)
	{
		waitpid(tmp->pid, &g_is_tricky.g_ret, 0);
		handle_return_value(&g_is_tricky.g_ret);
		tmp = tmp->next;
	}
	struct_pid_clear(&shell->childs);
}

static void	main_loop(t_minishell *shell)
{
	t_token	*token;
	int		curr_pipe;

	token = shell->tokens;
	curr_pipe = 0;
	if (pipes_count(shell) == 0)
		set_redirection(shell);
	while (token)
	{
		if (shell->error)
			break ;
		if (token->skip == TRUE || token->type >= REDIR_OUT)
		{
			if (token->type >= REDIR_OUT)
				token->next->skip = TRUE;
			token = token->next;
			continue ;
		}
		if (token->type == PIPE)
			execute_pipe(shell, token, &curr_pipe);
		if (token->type <= BUILTIN && !have_to_wait(shell))
			execute_token(shell, token);
		token = get_next_token(token);
	}
	wait_forks(shell);
}

void	execution(t_minishell *shell)
{
	g_is_tricky.g_run = TRUE;
	main_loop(shell);
	g_is_tricky.g_run = FALSE;
	unlink("here_doc");
	if (dup2(shell->in, STDIN) == -1)
		perror("minishell");
	if (dup2(shell->out, STDOUT) == -1)
		perror("minishell");
	close_fd_save(shell->in);
	close_fd_save(shell->out);
	close_fd_save(shell->fd_out);
	close_fd_save(shell->fd_in);
	free(shell->message);
}
