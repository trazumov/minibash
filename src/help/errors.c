/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:28:40 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/13 19:57:15 by mlatashi         ###   ########.fr       */
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
