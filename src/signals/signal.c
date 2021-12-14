/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:39:17 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/14 17:40:15 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_nothing(void)
{
	return ;
}

void	ft_signal(int code)
{
	if (code == SIGINT && !g_is_tricky.g_run)
	{
		g_is_tricky.g_ret = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (code == SIGQUIT && !g_is_tricky.g_run)
		do_nothing();
	if (g_is_tricky.g_run)
	{
		g_is_tricky.g_run = FALSE;
		if (code == SIGQUIT)
			ft_putstr_fd("Quit\n", 1);
		else if (code == SIGINT)
			ft_putstr_fd("\n", 1);
	}
}

/*
Обработка нажатия Ctrl + D что по сути является вызовом EOF
*/
void	on_eof(t_minishell *shell)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("exit\n", 1);
	shell->exit = TRUE;
}

int	ctrl_d(t_minishell *shell, char *input)
{
	if (input == NULL)
	{
		on_eof(shell);
		return (TRUE);
	}
	return (FALSE);
}
