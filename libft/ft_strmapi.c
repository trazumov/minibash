/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:50 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:51 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Applies the function ’f’ to each character of the
string ’s’ to create a new string (with malloc(3))
resulting from successive applications of ’f’.
RETURN The string created from the successive applications
of ’f’.  Returns NULL if the allocation fails.*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	index;

	if (!s || !f)
		return (NULL);
	res = (char *)malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}
