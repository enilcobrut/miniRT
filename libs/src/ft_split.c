/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:46:10 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:12 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_counter(char const *s, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char **ft_split(char const *s, char c)
{
	char **t;
	int i;
	int cursor;
	int j;

	if (!s)
		return (0);
	t = ft_calloc(word_counter(s, c) + 1 , sizeof(char *));
	if (!t)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		cursor = 0;
		while (s[i] == c)
			i++;
		if (s[i] == 0)
			break ;
		while (s[i + cursor] && s[i + cursor] != c)
 			cursor++;
		t[j++] = ft_substr(&s[i], 0, cursor);
		while (s[i] && s[i] != c)
			i++;
	}
	t[j++] = 0;
	return (t);
}	