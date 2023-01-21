/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:55:24 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:12 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_valid_set(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
			return (1);
		j++;
	}
	j = 0;
	return (0);
}

static unsigned int	ft_counter_str(char const *s1, char const *set)
{
	int	count;

	count = 0;
	while (s1[count] && (ft_valid_set(&s1[count], set) == 1))
		count++;
	return (count);
}

static unsigned int	ft_reverse_counter_str(char const *s1, char const *set)
{
	int	count;

	count = ft_strlen(s1) - 1;
	while (count > 0 && (ft_valid_set(&s1[count], set) == 1))
		count--;
	return (count + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		start;
	unsigned int		end;
	char				*tmp;

	if (!s1 || !set)
		return (0);
	start = ft_counter_str(s1, set);
	end = ft_strlen(s1) - ft_reverse_counter_str(s1, set);
	tmp = ft_substr(s1, start, (size_t)((ft_strlen(s1) - start - end)));
	return (tmp);
}
