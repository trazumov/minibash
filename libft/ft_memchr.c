/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:05 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:05 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*locates the first occurrence of c in string s*/
/*returns a pointer to the byte located*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;
	unsigned char	tmp;
	unsigned int	i;

	res = (unsigned char *)s;
	tmp = (unsigned char)c;
	i = 0;
	while (n > 0)
	{
		if (res[i] == tmp)
			return (&res[i]);
		i++;
		n--;
	}
	return (NULL);
}
