#include "../parser.h"
#include "../libft/libft.h"

char	**realloc_environ(int diff, char *str)
{
	int		size;
	int		i;
	char	**arr;

	size = get_env_size(__environ);
	arr = malloc(sizeof(char *) * (size + 1 + diff));
	if (diff > 0)
	{
		i = -1;
		while (++i < size)
		{
			arr[i] = ft_strdup(__environ[i]);
			free(__environ[i]);
		}
		arr[i] = ft_strdup(str);
	}
	else
		handle_negative_diff(arr, str, size);
	free(__environ);
	arr[size + diff] = NULL;
	return (arr);
}

void	insertion_sort(char **arr, int size)
{
	char	*temp;
	int		i;
	int		k;

	i = 1;
	while (i < size)
	{
		k = i;
		while (k > 0 && ft_strcmp(arr[k], arr[k - 1]) < 0)
		{
			temp = arr[k];
			arr[k] = arr[k - 1];
			arr[k - 1] = temp;
			k--;
		}
		i++;
	}
}

void	print_sorted_env(void)
{
	char	**arr;
	int		size;
	int		i;

	arr = malloc_environ();
	size = get_env_size(arr);
	insertion_sort(arr, size);
	i = -1;
	while (arr[++i])
	{
		printf("declare -x %s\n", arr[i]);
		free(arr[i]);
	}
	free(arr);
}

int	check_var_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (2);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (2);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	print_export_or_unset_error(char *str, int type)
{
	if (type == 1)
		ft_putstr_fd("minishell: export: «", 2);
	else
		ft_putstr_fd("minishell: unset: «", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("»: not a valid identifier", 2);
	return (1);
}

void	add_var(char *var_name, char *str)
{
	int		i;
	int		len;

	i = 0;
	if (getenv(var_name))
	{
		len = ft_strlen(var_name) + 1;
		while (__environ[i])
		{
			if (ft_strncmp(str, __environ[i], len) == 0)
			{
				free(__environ[i]);
				__environ[i] = ft_strdup(str);
				free(var_name);
				return ;
			}
			i++;
		}
	}
	__environ = realloc_environ(1, str);
	free(var_name);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

int	ft_export(t_token *token)
{
	int		ret;

	if (token == NULL || (token && token->type != ARG))
		print_sorted_env();
	else
	{
		while (token && token->type == ARG)
		{
			ret = check_var_name(token->str);
			if (ret == 2)
				return (print_export_or_unset_error(token->str, 1));
			else if (ret == 0)
				add_var(get_var_name(token->str), token->str);
			token = token->next;
		}
	}
	return (0);
}
