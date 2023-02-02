
#include "miniRT_bonus.h"

t_light	*lst_new_light(int nb)
{
	t_light	*new;

	new = ft_calloc(1, sizeof(t_light));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->n = nb;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_light	*lst_add_light(t_light **lst, t_light *new)
{
	t_light	*current;

	if (*lst == NULL || size_light(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_light(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_light(lst);
	return (current);
}

t_light	*lst_last_light(t_light **lst)
{
	t_light	*tmp;

	if (!*lst || size_light(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_light(t_light *lst)
{
	t_light	*current;
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
