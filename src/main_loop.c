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
	if (next_type == CMD || next_type == ARG)
	{
		res = token->next;
		while (res && (res->type == CMD || res->type == ARG))
			res = res->next;
	}
	return (res);
}

static t_token *get_prev_redir(t_token *token)
{
	t_token *res;

	res = token->prev;
	while (res && res->type != REDIR_OUT_2 && res->type != REDIR_OUT)
		res = res->prev;
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

// TRUE если следующий токен это PIPE
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

static int get_redirection(t_minishell *shell)
{
	t_token *token;

	shell->is_redir = FALSE;
	token = shell->tokens;
	while (token)
	{
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
		{
			if (shell->is_redir)
			{
				// сделать предыдущий редирект скипнутым
				get_prev_redir(token)->skip = TRUE;
				close(shell->fd_out);
			}
			if (token->next)
			{
				if (token->type == REDIR_OUT)
					shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
				if (token->type == REDIR_OUT_2)
					shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
				shell->is_redir = TRUE;
			}
			else
				shell->fd_out = -1;
			if (!shell->fd_out)
				return (open_file_error(shell));
		}
		token = token->next;
	}
	return (shell->is_redir);
}

static void execute_token(t_token *token, char **envp)
{
	if (token->type == CMD)
		execute_last_cmd(token, envp);
	if (token->type == BUILTIN)
		execute_builtin(token, envp);
}

void	main_body(t_minishell *shell, char **envp)
{
	t_token *token;

	token = shell->tokens;
	shell->is_redir = get_redirection(shell);
	while (token)
	{
		// PIPES START
		if (token->type == PIPE && is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token), envp);
			execute_pipe_cmd(token->next, envp);
		}
		else if (token->type == PIPE && !is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token), envp);
			if (is_next_redir(token->next))
				dup2(shell->fd_out, STDOUT);
			execute_token(token->next, envp);
		}
		// PIPES END
		// CMD START
		else if ((token->type == CMD  || token->type == BUILTIN) \
		&& !is_next_pipe(token) && !is_next_redir(token))
		{
			execute_token(token, envp);
		}
		// CMD END
		// REDIR START
		else if ((token->type == REDIR_OUT || token->type == REDIR_OUT_2) \
		&& get_prev_token(token)->type != PIPE && !token->skip)
		{
			dup2(shell->fd_out, STDOUT);
			execute_token(get_prev_token(token), envp);
		}
		// REDIR END
		token = get_next_token(token);
	}
}

void	execution(t_minishell *shell, char **envp)
{
	main_body(shell, envp);
	// восстанавливаем чтение и вывод как было
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
	close(shell->in);
	close(shell->out);
	if (shell->is_redir)
		close(shell->fd_out);
	// восстанавливаем чтение и вывод как было
}