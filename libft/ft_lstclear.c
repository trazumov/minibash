/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:23:42 by svirgil           #+#    #+#             */
/*   Updated: 2021/09/24 13:23:43 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*to_del;

	to_del = *lst;
	while (to_del)
	{
		tmp = to_del->next;
		if (del)
			del(to_del->content);
		free(to_del);
		to_del = tmp;
	}
	*lst = NULL;
}
