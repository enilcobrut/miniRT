/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:42:52 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:12 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len] != '\0')
		len++;
	return (len);
}

int	search_endl_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}	
	return (-1);
}

char	*ft_substr_gnl(char *str, int start, int end)
{
	int			i;
	char		*new_str;

	i = 0;
	if (!str || *str == 0 || start > end)
		return (0);
	new_str = ft_calloc(((end - start) + 1), sizeof(char));
	if (!new_str)
		return (0);
	while (str[i] && i < (end - start))
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
