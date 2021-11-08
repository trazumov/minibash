#include "../includes/minishell.h"

t_token *create_tmp_token(void)
{
	t_token *tmp;

	tmp = malloc(sizeof(t_token));
	//
	tmp->type = TYPE_CMD;
	tmp->next = NULL;
	tmp->argv = malloc(sizeof(char *) * 3);
	tmp->argv[0] = ft_strdup("ls");
	tmp->argv[1] = ft_strdup("-l");
	tmp->argv[2] = NULL;
	//
	return tmp;
}