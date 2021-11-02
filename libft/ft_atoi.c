/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:22:57 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:22:58 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*converts the initial portion of string to int*/
int	ft_atoi(const char *str)
{
	int				res;
	int				sign;
	unsigned char	*tmp;

	sign = 1;
	res = 0;
	tmp = (unsigned char *)str;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (*tmp == '-')
		sign = -1;
	if ((*tmp == '-') || (*tmp == '+'))
		tmp++;
	while (*tmp && *tmp >= '0' && *tmp <= '9')
	{
		res = res * 10 + (*tmp - 48);
		tmp++;
	}
	return (res * sign);
}
