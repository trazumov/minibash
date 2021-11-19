#include "../parser.h"
#include "../libft/libft.h"

int	is_name_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_negative_diff(char **arr, char *str, int size)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	j = 0;
	i = -1;
	while (++i < size)
	{
		if (ft_strncmp(str, __environ[i], len) == 0 && __environ[i][len] == '=')
		{
			free(__environ[i]);
			continue ;
		}
		arr[j] = ft_strdup(__environ[i]);
		free(__environ[i]);
		j++;
	}
}

void	ft_unset(t_token *token)
{
	while (token && token->type == ARG)
	{
		if (is_name_valid(token->str) && getenv(token->str))
			__environ = realloc_environ(-1, token->str);
		else if (is_name_valid(token->str) == 0)
			print_export_or_unset_error(token->str, 2);
		token = token->next;
	}
}
