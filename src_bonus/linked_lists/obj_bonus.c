
#include "miniRT_bonus.h"

t_obj	*lst_new_obj(int type)
{
	t_obj	*new;
	
	new = ft_calloc(1, sizeof(t_obj));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->type = type;
	new->n = 0;
	new->xpm = NULL;
	new->bump_map = NULL;
	new->bump_map_addr = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_obj	*lst_add_obj(t_obj **lst, t_obj *new)
{
	t_obj	*current;

	if (*lst == NULL || size_obj(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_obj(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_obj(lst);
	return (current);
}

t_obj	*lst_last_obj(t_obj **lst)
{
	t_obj	*tmp;

	if (!*lst || size_obj(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_obj(t_obj *lst)
{
	t_obj	*current;
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
