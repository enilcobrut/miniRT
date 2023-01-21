/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:17:42 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:12 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*tmp;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (0);
	tmp[0] = 0;
	if (start >= ft_strlen(s))
		return (tmp);
	while (s[i] && i < len)
	{
		tmp[i] = s[(size_t)start + i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
