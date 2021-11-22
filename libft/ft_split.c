/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:44:40 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/28 20:26:32 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_sep(char const *s, char c)
{
	int	i;
	int	sep;

	i = 0;
	sep = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			sep++;
			while (s[i] == c && s[i] != '\0')
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		sep++;
	return (sep);
}

static void	ft_length(int *len, int *i, char const *s, char c)
{
	*len = 0;
	while (s[*i] != '\0' && s[*i] == c)
		(*i)++;
	while (s[*i] != c && s[*i] != '\0')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}

static char	**ft_malloc_fail(char **res, int j)
{
	j -= 1;
	while (j >= 0)
	{
		free(res[j]);
		j--;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		len;
	int		size;

	if (s == NULL)
		return (NULL);
	size = ft_count_sep(s, c);
	res = malloc((size + 1) * sizeof(*res));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < size)
	{
		ft_length(&len, &i, s, c);
		res[j] = malloc((len + 1) * sizeof(**res));
		if (res[j] == NULL)
			return (ft_malloc_fail(res, j));
		ft_memcpy(res[j], s + (i - 1 - len), len);
		res[j][len] = '\0';
	}
	res[j] = NULL;
	return (res);
}
