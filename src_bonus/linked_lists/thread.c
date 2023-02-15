/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:47:28 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:47:33 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_th	*init_th_lst(t_th *new)
{
	return (new);
}

t_th	*lst_new_th(int n)
{
	t_th	*new;

	new = ft_calloc(1, sizeof(t_th));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->n = n;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_th	*lst_add__th(t_th **lst, t_th *new)
{
	t_th	*current;

	if (*lst == NULL || size_th(*lst) == 0)
		*lst = new;
	else
	{
		current = lst_last_th(lst);
		current->next = new;
		current->next->prev = current;
	}
	current = lst_last_th(lst);
	return (current);
}

t_th	*lst_last_th(t_th **lst)
{
	t_th	*tmp;

	if (!*lst || size_th(*lst) == 0)
		return (*lst);
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	size_th(t_th *lst)
{
	t_th	*current;
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
