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

int set_redirection(t_minishell *shell)
{
	t_token *token;
	int		new_input;
	int		new_output;

	new_output = FALSE;
	new_input = FALSE;
	token = shell->tokens;
	while (token)
	{
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
		{
			if (new_output)
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
				new_output = TRUE;
			}
			else
				shell->fd_out = -1;
			if (!shell->fd_out)
				return (open_file_error(shell));
		}
		if (token->type == REDIR_IN)
		{
			if (new_input == TRUE)
			{
				get_prev_input(token)->skip = TRUE;
				close(shell->fd_in);
			}
			if (token->next)
			{
				if (token->type == REDIR_IN)
					shell->fd_in = open(token->str, O_RDONLY, S_IRWXU);
				new_input = TRUE;
			}
			else
				new_input = -1;
			if (!new_input)
				return (open_file_error(shell));
		}
		token = token->next;
	}
	return (0);
}