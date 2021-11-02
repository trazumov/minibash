/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:40:32 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/27 23:38:45 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptrd;
	unsigned const char	*ptrs;

	ptrd = dst;
	ptrs = src;
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		if (ptrs[i] == (unsigned char) c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
