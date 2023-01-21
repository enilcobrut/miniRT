/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:53:23 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:13 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_plane	*init_plane(t_plane *new)
{
	return (new);
}

t_plane	*lst_new_plane(void)
{
	t_plane	*new;

	new = ft_calloc(1, sizeof(t_plane));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_plane	*lst_add__plane(t_plane **lst, t_plane *new)
{
	t_plane	*current;

	if (*lst == NULL || size_plane(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_plane(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_plane(lst);
	return (current);
}

t_plane	*lst_last_plane(t_plane **lst)
{
	t_plane	*tmp;

	if (!*lst || size_plane(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_plane(t_plane *lst)
{
	t_plane	*current;
	int		size;

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
