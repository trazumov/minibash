#include "../includes/minishell.h"

// для введенного токена ищет следующий
static t_token *get_next_token(t_token *token) // CMD PIPE REDIR_OUT
{
	t_token *res;
	int		next_type;

	if (token->next == NULL)
		return (NULL);
	next_type = token->next->type;
	if (next_type == PIPE || next_type == REDIR_OUT || next_type == REDIR_OUT_2)
		return token->next;
	if (token->type == PIPE)
		res = token->next;
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

static t_token *get_prev_token(t_token *token) // CMD PIPE
{
	t_token *res;

	if (token->prev == NULL)
		return (NULL);
	else if (token->prev->type == PIPE) // is CMD and prev PIPE
		return (token->prev);
	else
	{
		res = token->prev;
		while (res->prev && res->prev->type != PIPE)
			res = res->prev;
	}
	return (res);
}

static int	is_next_pipe(t_token *token)
{
	t_token *res;

	res = get_next_token(token);
	if (res && res->type == PIPE)
		return TRUE;
	return FALSE;
}

static int	is_next_redir(t_token *token)
{
	t_token *res;

	res = get_next_token(token);
	if (res && (res->type == REDIR_OUT || res->type == REDIR_OUT_2))
		return TRUE;
	return FALSE;
}

static void execute_token(t_minishell *shell, t_token *token)
{
	if (token->type == CMD || token->type == ARG) // убрать
		execute_last_cmd(token);
	else if (token->type == BUILTIN)
		execute_builtin(shell, token);
}

void	main_body(t_minishell *shell)
{
	t_token *token;

	token = shell->tokens;
	set_redirection(shell);
	while (token)
	{
		if (token->skip == TRUE || token->type >= REDIR_OUT)
		{
			if (token->type >= REDIR_OUT)
				token->next->skip = TRUE;
			token = token->next;
			continue ;
		}
		if (token->type == PIPE && is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token));
			execute_pipe_cmd(token->next);
		}
		else if (token->type == PIPE && !is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token));
			execute_token(shell, token->next);
		}
		else if (token->type <= BUILTIN && !is_next_pipe(token))
			execute_token(shell, token);
		token = get_next_token(token);
	}
}

static void ft_close(int fd)
{
	if (fd)
		close(fd);
}

void	execution(t_minishell *shell)
{
	main_body(shell);
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
	close(shell->in);
	close(shell->out);
	ft_close(shell->fd_out);
	ft_close(shell->fd_in);
	free(shell->message);
}