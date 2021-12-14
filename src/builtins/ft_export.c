/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:26 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/13 20:00:17 by mlatashi         ###   ########.fr       */
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
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	add_var(char *var_name, char *str)
{
	int		index;

	index = ft_is_in_env(var_name);
	free(var_name);
	if (index && ft_strchr(str, '='))
	{
		free(__environ[index - 1]);
		__environ[index - 1] = ft_strdup(str);
	}
	else if (index && !ft_strchr(str, '='))
		return ;
	else
		__environ = realloc_environ(1, str);
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
	int	ret;

	ret = 0;
	if (token == NULL || (token && token->type != ARG))
		print_sorted_env();
	else
	{
		while (token && token->type == ARG)
		{
			if (check_var_name(token->str) == 1)
				ret = print_export_or_unset_error(token->str, 1);
			else
				add_var(get_var_name(token->str), token->str);
			token = token->next;
		}
	}
	return (ret);
}
