/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:53:14 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:13 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere	*init_sphere_lst(t_sphere *new)
{
	return (new);
}

t_sphere	*lst_new_sphere(void)
{
	t_sphere	*new;

	new = ft_calloc(1, sizeof(t_sphere));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sphere	*lst_add__sphere(t_sphere **lst, t_sphere *new)
{
	t_sphere	*current;

	if (*lst == NULL || size_sphere(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_sphere(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_sphere(lst);
	return (current);
}

t_sphere	*lst_last_sphere(t_sphere **lst)
{
	t_sphere	*tmp;

	if (!*lst || size_sphere(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_sphere(t_sphere *lst)
{
	t_sphere	*current;
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
