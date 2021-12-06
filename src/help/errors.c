/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:28:40 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/06 21:29:10 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file_error(t_minishell *shell)
{
	ft_putstr_fd(shell->message, STDERR);
	ft_putstr_fd(shell->tokens->str, STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	shell->ret = 1;
	return (-1);
}
