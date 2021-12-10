/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:43:02 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:53:07 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_arg_numeric(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_token *token, t_minishell *shell)
{
	unsigned int	ret;

	ft_putendl_fd("exit", 2);
	if (token && is_arg_numeric(token->str) == 0)
	{
		ret = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (token && token->next)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else if (token)
		ret = ft_atoi(token->str);
	else
		ret = 0;
	shell->exit = TRUE;
	return (ret);
}
