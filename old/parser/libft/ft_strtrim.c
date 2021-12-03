/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:59:57 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/28 22:44:20 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		trim_ct;
	char	*res;

	if (s1 == NULL)
		return (NULL);
	i = -1;
	trim_ct = 0;
	while (s1[++i] != '\0' && ft_strchr(set, s1[i]))
	{
		trim_ct++;
	}
	j = ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, s1[j]))
	{
		j--;
		trim_ct++;
	}
	res = malloc((ft_strlen(s1) - trim_ct + 1) * sizeof(*res));
	if (res == NULL)
		return (res);
	ft_memcpy(res, s1 + i, ft_strlen(s1) - trim_ct);
	res[ft_strlen(s1) - trim_ct] = '\0';
	return (res);
}
