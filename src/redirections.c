#include "../includes/minishell.h"

static t_token *get_prev_redir(t_token *token)
{
	t_token *res;

	res = token->prev;
	while (res && res->type != REDIR_OUT_2 && res->type != REDIR_OUT)
		res = res->prev;
	return (res);
}

static t_token *get_prev_input(t_token *token)
{
	t_token *res;

	res = token->prev;
	while (res && res->type != REDIR_IN)
		res = res->prev;
	return (res);
}

// return 0 if OK ; return 1 if ERROR
static int redirect_out(t_minishell *shell, t_token *token, int *new_output)
{
	if (*new_output)
	{
		get_prev_redir(token)->skip = TRUE;
		close(shell->fd_out);
	}
	if (token->next)
	{
		if (token->type == REDIR_OUT)
			shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (token->type == REDIR_OUT_2)
			shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		dup2(shell->fd_out, STDOUT);
		(*new_output) = TRUE;
	}
	else
		shell->fd_out = -1;
	if (!shell->fd_out)
		return (1);
	return (0);
}

static int redirect_in(t_minishell *shell, t_token *token, int *new_input)
{
	if ((*new_input) == TRUE)
	{
		get_prev_input(token)->skip = TRUE;
		close(shell->fd_in);
	}
	if (token->next)
	{
		if (token->type == REDIR_IN)
			shell->fd_in = open(token->next->str, O_RDONLY, S_IRWXU);
		dup2(shell->fd_in, STDIN);
		(*new_input) = TRUE;
	}
	else
		(*new_input) = -1;
	if (!(*new_input))
		return (1);
	return (0);
}

static int redirect_heredoc(t_minishell *shell, t_token *token, int *new_input)
{
	if ((*new_input) == TRUE)
	{
		get_prev_input(token)->skip = TRUE;
		close(shell->fd_in);
	}
	if (token->next)
	{
		if (token->type == REDIR_HEREDOC)
			exec_here_doc(shell, token);
		(*new_input) = TRUE;
	}
	else
		(*new_input) = -1;
	if (!(*new_input))
		return (1);
	return (0);
}

int set_redirection(t_minishell *shell)
{
	t_token	*token;
	int		new_input;
	int		new_output;

	new_output = FALSE;
	new_input = FALSE;
	token = shell->tokens;
	while (token)
	{
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
			if (redirect_out(shell, token, &new_output))
				return (open_file_error(shell));
		if (token->type == REDIR_IN)
			if (redirect_in(shell, token, &new_input))
				return (open_file_error(shell));
		if (token->type == REDIR_HEREDOC)
			if (redirect_heredoc(shell, token, &new_input))	
				return (open_file_error(shell));
		token = token->next;
	}
	return (0);
}