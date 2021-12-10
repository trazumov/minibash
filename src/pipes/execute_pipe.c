/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:50:45 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 17:55:47 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (FALSE);
		tmp = tmp->prev;
	}
	return (TRUE);
}

static int	have_next_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

static int	is_mid_pipe(t_token *token)
{
	t_token	*prev;
	int		res;

	prev = token->prev;
	res = have_next_pipe(token->next);
	while (prev)
	{
		if (prev->type == PIPE)
		{
			res++;
			break ;
		}
		prev = prev->prev;
	}
	if (res == 2)
		return (TRUE);
	return (FALSE);
}

static int	is_last_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

void	execute_pipe(t_minishell *shell, t_token *token, int *curr_pipe)
{
	int		pipes_cnt;
	t_token	*tmp;

	tmp = shell->tokens;
	pipes_cnt = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipes_cnt++;
		tmp = tmp->next;
	}
	if (pipes_cnt == 1)
		the_only_pipe(shell, token, *curr_pipe);
	else if (is_first_pipe(token))
		first_pipe(shell, token, *curr_pipe);
	else if (is_mid_pipe(token))
		mid_pipe(shell, token, *curr_pipe);
	else if (is_last_pipe(token))
		last_pipe(shell, token, *curr_pipe);
	(*curr_pipe)++;
}
