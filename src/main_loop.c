#include "../includes/minishell.h"

// для введенного токена ищет следующий
static t_token *get_next_token(t_token *token) // CMD PIPE REDIR_OUT
{
	t_token *res;
	int		next_type;

	if (token->next == NULL)
		return (NULL);
	next_type = token->next->type;
	if (next_type == PIPE || next_type == REDIR_OUT)
		return token->next;
	if (token->type == PIPE)
		res = token->next;
	if (token->type == REDIR_OUT)
		res = token->next;
	if (next_type == CMD || next_type == ARG)
	{
		res = token->next;
		while (res && (res->type == CMD || res->type == ARG))
			res = res->next;
	}
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
	if (res && res->type == REDIR_OUT)
		return TRUE;
	return FALSE;
}

/*
static void redirect_and_execute(t_minishell *shell, t_token *token, char **envp)
{
	shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (!shell->fd_out)
		return (open_file_error(shell));
	//dup2(shell->fd_out, STDOUT);
	//execute_last_cmd(get_prev_token(token), envp);
}
*/

static int get_redirection(t_minishell *shell)
{
	t_token *token;

	token = shell->tokens;
	while (token)
	{
		if (token->type == REDIR_OUT)
		{
			if (shell->is_redir)
				close(shell->fd_out);
			if (token->next)
				shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			else
				shell->fd_out = -1;
			if (!shell->fd_out)
				return (open_file_error(shell));
		}
		token = token->next;
	}
	
	return (FALSE);
}

void	main_body(t_minishell *shell, char **envp)
{
	t_token *token;

	token = shell->tokens;
	shell->is_redir = get_redirection(shell);
	while (token)
	{
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
			execute_last_cmd(token->next, envp);
		}
		else if (token->type == CMD && !is_next_pipe(token) && !is_next_redir(token))
		{
			execute_last_cmd(token, envp);
		}
		else if (token->type == REDIR_OUT && get_prev_token(token)->type != PIPE)
		{
			dup2(shell->fd_out, STDOUT);
			execute_last_cmd(get_prev_token(token), envp);
		}
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