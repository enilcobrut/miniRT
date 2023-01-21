/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:13:55 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/12 13:43:53 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = ft_strlen(s);
	if (!s)
		return (0);
	if (s != NULL || c != '0')
	{
		while (s[i])
		{	
			if (s[i] == (char)c)
				return (&((char *)s)[i]);
			if (i == 0)
				return (0);
			i--;
		}
	}
	return (0);
}
