/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 23:16:43 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/28 22:14:59 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) >= len)
		res = malloc((len + 1) * sizeof(*res));
	else
		res = malloc((ft_strlen(s) + 1) * sizeof(*res));
	if (res == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res[0] = '\0';
		return (res);
	}
	i = 0;
	while (i < len && s[start] != '\0')
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
