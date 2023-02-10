/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:59:22 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/10 12:00:58 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*init_obj_lst(t_obj *new)
{
	return (new);
}

t_obj	*lst_new_obj(int type)
{
	t_obj	*new;

	new = ft_calloc(1, sizeof(t_obj));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->type = type;
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
