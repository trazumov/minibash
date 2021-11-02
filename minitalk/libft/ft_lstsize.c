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
