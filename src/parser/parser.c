/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:11:30 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/13 19:44:45 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_array(char *str, char **array, t_parser *vars)
{
	int	i;
	int	j;
	int	last_space;

	i = vars->i;
	j = vars->j;
	last_space = vars->last_space;
	array[j] = ft_substr(str, last_space, i - last_space);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (str[i] != '|' && (str[i + 1] == '>' || str[i + 1] == '<'))
			array[++j] = ft_substr(str, i++, 2);
		else
			array[++j] = ft_substr(str, i, 1);
		while (ft_isspace(str[++i]))
			continue ;
	}
	vars->last_space = i;
	vars->j = j + 1;
	vars->i = i - 1;
}

char	*parser(char *str, char **array, int token_ct)
{
	t_parser	var;

	var.i = 0;
	var.j = 0;
	while (ft_isspace(str[var.i]))
		(var.i)++;
	var.last_space = var.i;
	while (str[var.i] != '\0')
	{
		if (str[var.i] == '\'')
			str = handle_quotes(str, &var.i);
		else if (str[var.i] == '"')
			str = handle_double_quotes(str, &var.i);
		else if (str[var.i] == '$')
			str = handle_bucks(str, &var.i);
		else if (ft_issep(str[var.i]))
			add_to_array(str, array, &var);
		(var.i)++;
	}
	if (str[var.last_space] != '\0')
		array[var.j] = ft_substr(str, var.last_space, var.i - var.last_space);
	else if (str[var.last_space] == '\0' && var.j < token_ct)
		array[var.j] = ft_substr(str, var.last_space, var.i - var.last_space);
	return (str);
}

char	*parse(t_token **token, char *str)
{
	char	**array;
	int		sep_ct;

	sep_ct = 0;
	if (check_leading_pipe(str) == -1 || preparser(str, &sep_ct) == -1)
	{
		free(str);
		g_is_tricky.g_ret = 2;
		return (NULL);
	}
	array = malloc((sep_ct + 1) * sizeof(*array));
	if (array == NULL)
		malloc_error();
	str = parser(str, array, sep_ct + 1);
	create_tokens(token, array, sep_ct + 1);
	free(array);
	return (str);
}
