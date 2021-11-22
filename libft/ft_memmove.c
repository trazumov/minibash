/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:17:09 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/23 20:25:46 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*ptrd;
	const char	*ptrs;

	ptrs = src;
	ptrd = dst;
	if (ptrs < ptrd)
	{
		i = len;
		while (i > 0)
		{
			i--;
			ptrd[i] = ptrs[i];
		}
	}
	else if (ptrs > ptrd)
	{
		i = 0;
		while (i < len)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	return (dst);
}
