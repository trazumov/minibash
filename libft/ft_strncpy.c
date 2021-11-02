/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:54 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:54 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i] != '\0' & n-- > 0)
	{
		dest[i] = src[i];
		i++;
	}
	while (n-- > 0)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
