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
		return token->next; // ?
	if (token->type == PIPE)
		return token->next; // изменил, вроде логично стало
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

t_token *get_prev_token(t_token *token) // CMD PIPE
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

void execute_token(t_minishell *shell, t_token *token)
{
	if (token->type == CMD || token->type == ARG) // убрать
		execute_last_cmd(shell, token);
	else if (token->type == BUILTIN)
		execute_builtin(shell, token);
}

int have_to_wait(t_minishell *shell)
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

static int pipes_cnt(t_minishell *shell)
{
	t_token *tmp = shell->tokens;
	int res = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			res++;
		tmp = tmp->next;
	}
	return res;
}

static void execute_pipe(t_minishell *shell, t_token *token, int *curr_pipe)
{
	shell->wait_s = pipes_cnt(shell) + 1;
	if (shell->wait_s == 2)
		the_only_pipe(shell, token, *curr_pipe);
	else if (is_first_pipe(token))
		first_pipe(shell, token, *curr_pipe);
	else if (is_mid_pipe(token))
		mid_pipe(shell, token, *curr_pipe);
	else if (is_last_pipe(token))
		last_pipe(shell, token, *curr_pipe);
	(*curr_pipe)++;
}

static void wait_forks(t_minishell *shell)
{
	t_pid_t	*tmp;

	if (!have_to_wait(shell))
		return ;
	tmp = shell->childs;
	while (tmp)
	{
		waitpid(tmp->pid, &shell->ret, 0);
		tmp = tmp->next;
	}
	struct_pid_clear(&shell->childs);
}

void	main_body(t_minishell *shell)
{
	t_token	*token;
	int		curr_pipe;

	token = shell->tokens;
	curr_pipe = 0;
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
	g_is_executed = TRUE;
	main_body(shell);
	g_is_executed = FALSE;
	shell->ret = WEXITSTATUS(shell->ret); // ? sadasdasdasd
	unlink("here_doc");
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
	close(shell->in);
	close(shell->out);
	if (shell->fd_out)
		close(shell->fd_out);
	if (shell->fd_in)
		close(shell->fd_in);
	free(shell->message);
}