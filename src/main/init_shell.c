/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:35:49 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 17:54:45 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->message = ft_strdup("minishell$ ");
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->save_history = TRUE;
	shell->childs = NULL;
	shell->error = FALSE;
}
