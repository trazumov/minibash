/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:24:02 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/03 22:24:05 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_size(char **arr)
{
	int		size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
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

char	**malloc_environ(void)
{
	int		size;
	int		i;
	char	**arr;

	size = get_env_size(__environ);
	arr = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		arr[i] = ft_strdup(__environ[i]);
	arr[i] = NULL;
	return (arr);
}
