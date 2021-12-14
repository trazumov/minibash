/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:53:48 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/14 16:49:53 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
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

void	close_fd_save(int fd)
{
	if (fd >= 0)
		close (fd);
}

void	handle_return_value(int *return_value)
{
	if (WIFEXITED(*return_value))
		(*return_value) = WEXITSTATUS(*return_value);
	else if (WIFSIGNALED(*return_value))
	{
		(*return_value) = WTERMSIG(*return_value);
		if ((*return_value) == WIFSIGNALED_SIGINT)
			(*return_value) = SIGINT_STATUS;
		else if ((*return_value) == WIFSIGNALED_SIGQUIT)
			(*return_value) = SIGQUIT_STATUS;
	}
}

int	pipes_count(t_minishell *shell)
{
	int		pipes_cnt;
	t_token	*token;

	token = shell->tokens;
	pipes_cnt = 0;
	while (token)
	{
		if (token->type == PIPE)
			pipes_cnt++;
		token = token->next;
	}
	return (pipes_cnt);
}
