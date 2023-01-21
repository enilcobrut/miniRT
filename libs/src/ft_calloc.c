/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:08:27 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/08 18:07:59 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	else if (count == 0 || size == 0)
		p = malloc(1);
	else
	{
		p = malloc(count * size);
		if (p == NULL)
			return (0);
		ft_memset(p, 0, count * size);
	}
	return ((void *)p);
}
