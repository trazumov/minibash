/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:49:40 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/12 22:32:31 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_intermediate_strings(char *temp, char *part_1, char *part_2)
{
	free(temp);
	free(part_1);
	free(part_2);
}

char	*remove_invalid_var_name(char *str, char *var_name, int *start)
{
	int	i;
	int	len;

	len = ft_strlen(var_name) + 1;
	i = *start;
	while (str[i + len] != '\0')
	{
		str[i] = str[i + len];
		i++;
	}
	str[i] = '\0';
	*start -= 1;
	if (ft_strcmp(var_name, "1") != 0)
		free(var_name);
	return (str);
}

char	*replace_bucks(char *str, int i, int *start, char *var_value)
{
	char	*temp;
	char	*part_1;
	char	*part_2;

	part_1 = ft_substr(str, 0, *start);
	part_2 = ft_substr(str, i, ft_strlen(str) - i);
	temp = ft_strjoin(part_1, var_value);
	free(str);
	str = ft_strjoin(temp, part_2);
	*start = ft_strlen(temp) - 1;
	free_intermediate_strings(temp, part_1, part_2);
	return (str);
}

char	*handle_invalid_name(char *str, int *start)
{
	int	i;

	i = *start + 1;
	if (ft_isspace(str[i]) == 1 || str[i] == '\0')
		return (str);
	else if (ft_isalnum(str[i]) == 0)
		return (str);
	else
		return (remove_invalid_var_name(str, "1", start));
}

char	*handle_bucks(char *str, int *start)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = *start + 1;
	if (str[i] == '?')
	{
		var_value = ft_itoa(g_is_tricky.g_ret);
		str = replace_bucks(str, i + 1, start, var_value);
		free(var_value);
	}
	else
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
			return (handle_invalid_name(str, start));
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		var_name = ft_substr(str, *start + 1, i - *start - 1);
		var_value = getenv(var_name);
		if (var_value == NULL)
			return (remove_invalid_var_name(str, var_name, start));
		str = replace_bucks(str, i, start, var_value);
		free(var_name);
	}
	return (str);
}
