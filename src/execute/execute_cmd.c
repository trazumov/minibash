/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:53:51 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/14 20:52:39 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argv_size(t_token *token)
{
	int		res;
	t_token	*tmp;

	res = 1;
	tmp = token;
	while (tmp->next && (tmp->next->type == CMD || tmp->next->type == ARG))
	{
		tmp = tmp->next;
		res++;
	}
	return (res);
}

static char	**create_argv(t_token *token)
{
	int		size;
	int		i;
	char	**res;
	t_token	*tmp;

	i = 0;
	tmp = token;
	size = get_argv_size(tmp);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		malloc_error();
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		res[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	execv_cmd(t_token *token)
{
	char	**argv;

	argv = create_argv(token);
	simple_cmd(argv);
}

void	execute_last_cmd(t_token *token)
{
	pid_t	parent;
	char	**argv;

	argv = create_argv(token);
	parent = fork();
	if (parent)
	{
		waitpid(parent, &g_is_tricky.g_ret, 0);
		handle_return_value(&g_is_tricky.g_ret);
		free_char_list(argv);
	}
	else
		simple_cmd(argv);
}

void	execute_token(t_minishell *shell, t_token *token)
{
	if (token->type == CMD || token->type == ARG)
		execute_last_cmd(token);
	else if (token->type == BUILTIN)
		execute_builtin(shell, token);
}
