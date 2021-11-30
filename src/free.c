#include "../includes/minishell.h"

void free_char_list(char **list)
{
	int	i = 0;

	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

void	free_tokens(t_token **token)
{
	while ((*token)->next != NULL)
		(*token) = (*token)->next;
	while ((*token)->prev != NULL)
	{
		(*token) = (*token)->prev;
		free((*token)->next->str);
		(*token)->next->str = NULL;
		free((*token)->next);
		(*token)->next = NULL;
	}
	free((*token)->str);
	(*token)->str = NULL;
	free(*token);
	*token = NULL;
}
