/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:39:17 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/11 22:44:31 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_nothing(void)
{
	return ;
}

void	ft_signal_cmd(int code)
{
	if (code == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
	if (code == SIGINT)
		ft_putstr_fd("\n", 2);
}

void	ft_signal(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (code == SIGQUIT)
		do_nothing();
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
