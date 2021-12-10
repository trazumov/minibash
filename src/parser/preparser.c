/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:38:04 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:55:32 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_leading_pipe(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (parser_error(1, '|'));
	return (i);
}

int	handle_pipe(char *str, int i, int *sep_ct)
{
	i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '\0')
		return (parser_error(1, str[i]));
	(*sep_ct) += 2;
	return (i);
}

int	handle_redirection(char *str, int i, int *sep_ct)
{
	i++;
	if (str[i] == str[i - 1])
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issep(str[i]) || str[i] == '\0')
		return (parser_error(1, str[i]));
	(*sep_ct) += 2;
	return (i);
}

int	handle_sep(char *str, int i, int *sep_ct)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		i = handle_pipe(str, i, sep_ct);
	else if (str[i] == '>' || str[i] == '<')
		i = handle_redirection(str, i, sep_ct);
	else if (str[i] != '\0')
		(*sep_ct)++;
	return (i - 1);
}

int	preparser(char *str, int *sep_ct)
{
	int	i;
	int	quotes;
	int	dbl_quotes;

	quotes = 0;
	dbl_quotes = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' && !quotes && !dbl_quotes)
			quotes = 1;
		else if (str[i] == '"' && !quotes && !dbl_quotes)
			dbl_quotes = 1;
		else if (str[i] == '\'' && quotes)
			quotes = 0;
		else if (str[i] == '"' && dbl_quotes)
			dbl_quotes = 0;
		else if (ft_issep(str[i]) && !quotes && !dbl_quotes)
			i = handle_sep(str, i, sep_ct);
		if (i == -2)
			return (-1);
	}
	if (quotes || dbl_quotes)
		return (parser_error(2, 0));
	return (0);
}
