/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pid_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:29:50 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 17:55:03 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid_t	*struct_pid_new(pid_t value)
{
	t_pid_t	*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	if (new_elem == NULL)
		return (NULL);
	(*new_elem).pid = value;
	(*new_elem).next = NULL;
	return (new_elem);
}

static t_pid_t	*struct_pid_last(t_pid_t *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	struct_pid_add(t_pid_t **head, t_pid_t *new)
{
	t_pid_t	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = struct_pid_last(*head);
	last->next = new;
}

void	struct_pid_clear(t_pid_t **head)
{
	t_pid_t	*ptr;
	t_pid_t	*ptr_next;

	if (head == NULL)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		ptr_next = ptr->next;
		free(ptr);
		ptr = ptr_next;
	}
	*head = NULL;
}
