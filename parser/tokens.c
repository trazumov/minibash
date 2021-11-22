#include "libft/libft.h"
#include "parser.h"

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
		token->type = CMD;
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
