/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:51:35 by mlatashi          #+#    #+#             */
/*   Updated: 2021/04/25 05:36:23 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	n = n / 10;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_fill(char *res, int n, int len)
{
	int	i;

	i = len - 1;
	if (n >= 0)
	{
		while (i >= 0)
		{
			res[i] = (n % 10) + 48;
			n = n / 10;
			i--;
		}
	}
	else
	{
		n *= -1;
		res[0] = '-';
		while (i > 0)
		{
			res[i] = (n % 10) + 48;
			n = n / 10;
			i--;
		}
	}
	res[len] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	if (n == -2147483648)
	{
		res = malloc(sizeof(*res) * 12);
		if (res == NULL)
			return (NULL);
		ft_fill(res, n + 1, 11);
		res[10] = '8';
		return (res);
	}
	len = ft_length(n);
	res = malloc(sizeof(*res) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_fill(res, n, len);
	return (res);
}
