
#include "miniRT.h"

t_buf	*lst_new_buf(int x, int y, int hexa, int n_object)
{
	t_buf	*new;

	new = ft_calloc(1, sizeof(t_buf));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->x = x;
	new->y = y;
	new->hexa = hexa;
	new->n_object = n_object;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_buf	*lst_add_buf(t_buf **lst, t_buf *new)
{
	t_buf	*current;

	if (*lst == NULL || size_buf(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_buf(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_buf(lst);
	return (current);
}

t_buf	*lst_last_buf(t_buf **lst)
{
	t_buf	*tmp;

	if (!*lst || size_buf(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_buf(t_buf *lst)
{
	t_buf	*current;
	int			size;

	size = 0;
	if (lst)
	{
		current = lst;
		while (current)
		{
			size++;
			current = current->next;
		}
	}
	return (size);
}
