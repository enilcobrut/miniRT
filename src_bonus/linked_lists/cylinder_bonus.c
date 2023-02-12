/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:16:38 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 21:16:40 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_cylinder	*lst_new_cylinder(void)
{
	t_cylinder	*new;

	new = ft_calloc(1, sizeof(t_cylinder));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->diameter = 0;
	new->height = 0;
	new->radius = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cylinder	*lst_add__cylinder(t_cylinder **lst, t_cylinder *new)
{
	t_cylinder	*current;

	if (*lst == NULL || size_cylinder(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_cylinder(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_cylinder(lst);
	return (current);
}

t_cylinder	*lst_last_cylinder(t_cylinder **lst)
{
	t_cylinder	*tmp;

	if (!*lst || size_cylinder(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_cylinder(t_cylinder *lst)
{
	t_cylinder	*current;
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
