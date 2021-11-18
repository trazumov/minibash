#include "../includes/minishell.h"

// для введенного токена ищет следующий
static t_token *get_next_token(t_token *token) // CMD PIPE
{
	t_token *res;

	if (token->next == NULL)
		return (NULL);
	if (token->next->type == PIPE)
		return token->next;
	if (token->type == PIPE)
		res = token->next;
	if (token->next->type == CMD || token->next->type == ARG)
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

void	main_body(t_minishell *shell, t_token *token, char **envp)
{
	while (token)
	{
		if (token->type == PIPE && is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token), envp);
			execute_pipe_cmd(token->next, envp);
			token = get_next_token(token);
		}
		else if (token->type == PIPE && !is_next_pipe(token))
		{
			execute_pipe_cmd(get_prev_token(token), envp);
			execute_last_cmd(token->next, envp);
			token = get_next_token(token);
		}
		else if (token->type == CMD && !is_next_pipe(token))
		{
			execute_last_cmd(token, envp);
			token = get_next_token(token);
		}
		else // токен который привязан к пайпу, выполняется в секции PIPE
			token = get_next_token(token);
	}
}

void	execution(t_minishell *shell, char **envp)
{
	t_token *curr_token = shell->tokens; // чтобы не потерять

	main_body(shell, curr_token, envp);
	// восстанавливаем чтение и вывод как было
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
	close(shell->in);
	close(shell->out);
	// восстанавливаем чтение и вывод как было
}