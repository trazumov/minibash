/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:36 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:37 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*locates the first occurrence of c in s and locate \0*/
/*
char	*ft_strchr(const char *s, int c)
{
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)s;
	while (*res != (char)c)
	{
		if (*res == '\0')
			return (NULL);
		res++;
	}
	return (res);
}
*/
char	*ft_strchr(const char *s, int c)
{
	char			*res;
	unsigned int	i;

	res = (char *)s;
	i = 0;
	while (res[i] != (char)c)
	{
		if (res[i] == '\0')
			return (NULL);
		i++;
	}
	return (&res[i]);
}
