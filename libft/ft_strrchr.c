/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:59 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:59 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*locates the LAST occurrence of c (converted to a char) in
the string pointed to by s.  The terminating null character 
is considered to be part of the string;
therefore if c is `\0', the functions 
locate the terminating `\0'.*/
char	*ft_strrchr(const char *str, int ch)
{
	size_t			len;
	unsigned int	i;

	len = ft_strlen(str);
	i = 0;
	if ((char)ch == '\0')
		return ((char *)str + len);
	while (len-- > 0)
	{
		if (str[i + len] == (char)ch)
			return ((char *)&str[i + len]);
	}
	return (NULL);
}
