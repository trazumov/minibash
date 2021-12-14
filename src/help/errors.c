/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:28:40 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/14 20:46:54 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_error(void)
{
	g_is_tricky.g_ret = 1;
	return (-1);
}

void	malloc_error(void)
{
	ft_putendl_fd("Malloc error", 2);
	exit(EXIT_FAILURE);
}

int	return_shell_err(t_minishell *shell)
{
	shell->error = TRUE;
	perror("minishell");
	return (1);
}

void	exit_shell_err(t_minishell *shell)
{
	shell->error = TRUE;
	perror("minishell");
	exit(EXIT_FAILURE);
}

int	fatal_error(t_minishell *shell)
{
	if (shell-> error)
		return (1);
	if (g_is_tricky.g_run == FALSE)
		return (1);
	return (0);
}
