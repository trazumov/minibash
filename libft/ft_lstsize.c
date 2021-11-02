/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:00 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:24:01 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		list_len;
	t_list	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	list_len = 0;
	if (!lst)
		return (list_len);
	while (tmp)
	{
		list_len++;
		tmp = tmp->next;
	}
	return (list_len);
}
