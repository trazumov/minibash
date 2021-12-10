/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:33:22 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:55:24 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_issep(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

void	create_tokens(t_token **token, char **array, int token_ct)
{
	int	i;

	i = 0;
	while (i < token_ct)
	{
		ft_add_token(token, ft_new_token());
		if ((*token)->next)
			(*token) = (*token)->next;
		(*token)->str = ft_strdup(array[i]);
		assign_type(*token, array[i]);
		free(array[i]);
		i++;
	}
	while ((*token)->prev != NULL)
		(*token) = (*token)->prev;
}

int	parser_error(int type, char ch)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token «", 2);
		if (ch == '\0')
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(ch, 2);
		ft_putstr_fd("»\n", 2);
	}
	else
		ft_putendl_fd("minishell: syntax error near unclosed quote", 2);
	return (-1);
}
