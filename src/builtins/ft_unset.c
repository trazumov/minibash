/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:44:02 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:53:30 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_unset(t_token *token)
{
	int	ret;

	ret = 0;
	while (token && token->type == ARG)
	{
		if (is_name_valid(token->str) && getenv(token->str))
			__environ = realloc_environ(-1, token->str);
		else if (is_name_valid(token->str) == 0)
			ret = print_export_or_unset_error(token->str, 2);
		token = token->next;
	}
	return (ret);
}
