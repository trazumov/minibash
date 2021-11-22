/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:18:29 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/28 21:25:51 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
		{
			res = (char *)(s + i);
			return (res);
		}
		i++;
	}
	if (s[i] == (char) c)
	{
		res = (char *)(s + i);
		return (res);
	}
	return (NULL);
}
