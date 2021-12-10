/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:43:17 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:53:24 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
		return (0);
	}
	else
		return (1);
}
