/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:43 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:43 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*appends string src to the end of dst.  
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate, unless dstsize is 0 or the original dst 
string was longer than dstsize
If the src and dst strings overlap, the behavior is undefined.
RETURN the total length of the string they tried to create*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
		src_len += size;
	else
		src_len += dst_len;
	while (src[i] && (dst_len + 1) < size)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	return (src_len);
}
