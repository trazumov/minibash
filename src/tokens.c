#include "../includes/minishell.h"

t_token	*ft_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	(*new).type = -1;
	(*new).str = NULL;
	(*new).next = NULL;
	(*new).prev = NULL;
	return (new);
}

t_token	*ft_last_token(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_last_token(*lst);
	last->next = new;
	new->prev = last;
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0)
		return (1);
	else
		return (0);
}

void	assign_type(t_token *token, char *str)
{
	if (ft_strcmp(str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(str, ">") == 0)
		token->type = REDIR_OUT;
	else if (ft_strcmp(str, ">>") == 0)
		token->type = REDIR_OUT_2;
	else if (ft_strcmp(str, "<") == 0)
		token->type = REDIR_IN;
	else if (ft_strcmp(str, "<<") == 0)
		token->type = REDIR_HEREDOC;
	else if (token->prev == NULL || token->prev->type >= PIPE)
	{
		if (is_builtin(str))
			token->type = BUILTIN;
		else
			token->type = CMD;
	}
	else
		token->type = ARG;
}

void	create_tokens(t_token **token, char **array, int token_ct)
{
	int	i;

	i = 0;
	while (i < token_ct)
	{
		ft_add_token(token, ft_new_token());
		if ((*token)->next)
			(*token) = (*token)->next;
		(*token)->str = ft_strdup(array[i]);
		assign_type(*token, array[i]);
		free(array[i]);
		i++;
	}
	while ((*token)->prev != NULL)
		(*token) = (*token)->prev;
}
