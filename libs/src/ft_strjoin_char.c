/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:35:12 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/21 11:36:05 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const s2)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	tmp = ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (tmp == NULL)
		return (0);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = s2;
	tmp[i + 1] = '\0';
	return (tmp);
}
