/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:42:46 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/13 01:45:49 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		if (ft_strchr(__environ[i], '='))
			printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}
