
#include "miniRT_bonus.h"

t_cone	*lst_new_cone(void)
{
	t_cone	*new;

	new = ft_calloc(1, sizeof(t_cone));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->diameter = 0;
	new->height = 0;
	new->radius = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cone	*lst_add_cone(t_cone **lst, t_cone *new)
{
	t_cone	*current;

	if (*lst == NULL || size_cone(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_cone(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_cone(lst);
	return (current);
}

t_cone	*lst_last_cone(t_cone **lst)
{
	t_cone	*tmp;

	if (!*lst || size_cone(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_cone(t_cone *lst)
{
	t_cone	*current;
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
