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
