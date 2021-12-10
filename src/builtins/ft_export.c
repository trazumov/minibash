/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:26 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:53:13 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
