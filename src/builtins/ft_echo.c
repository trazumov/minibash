#include "../../includes/minishell.h"

int	ft_echo(t_token *token)
{
	int	option;

	option = 0;
	while (token && ft_strcmp(token->str, "-n") == 0)
	{
		token = token->next;
		option = 1;
	}
	while (token && token->type == ARG)
	{
		if (token->next && token->next->type == ARG)
			printf("%s ", token->str);
		else
			printf("%s", token->str);
		token = token->next;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
