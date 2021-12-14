/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:48:46 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/12 22:32:37 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i < end - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 2];
		i++;
	}
	str[i] = '\0';
}

char	*handle_quotes(char *str, int *start)
{
	int	end;

	end = *start + 1;
	while (str[end] != '\'')
		end++;
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}

char	*handle_double_quotes(char *str, int *start)
{
	int		end;

	end = *start + 1;
	while (str[end] != '"')
	{
		if (str[end] == '$')
			str = handle_bucks(str, &end);
		end++;
	}
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}
