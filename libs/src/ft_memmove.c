/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:38:10 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/12 13:36:18 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*lastd;
	const char	*lasts;

	d = dst;
	s = src;
	while (len > 0 && d < s)
	{
		*d++ = *s++;
		len--;
	}
	if (d > s)
	{
		lasts = s + (len - 1);
		lastd = d + (len - 1);
		while (len > 0)
		{
			*lastd-- = *lasts--;
			len--;
		}
	}
	return (dst);
}
