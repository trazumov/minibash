/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 23:11:31 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/28 20:28:52 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			k = i;
			while (haystack[k] == needle[j] && haystack[k] != '\0' && k < len)
			{
				k++;
				j++;
			}
			if (j == ft_strlen(needle))
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
