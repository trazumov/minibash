/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:42:21 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:52:50 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int	option;

	option = 0;
	while (token && ft_strcmp(token->str, "-n") == 0)
	{
		token = token->next;
		option = 1;
	}
	while (token && token->type == ARG)
	{
		if (token->next && token->next->type == ARG)
			printf("%s ", token->str);
		else
			printf("%s", token->str);
		token = token->next;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
