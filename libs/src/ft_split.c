/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:46:10 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 11:20:03 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pointer_counter(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static struct s_map	*ft_cut(struct s_map *map, char const *s, char c, int i)
{
	int	t;
	int	counter;

	t = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (s[i] != c && counter == 0)
			{
				map[t].start = i;
			}
			counter++;
			i++;
		}
		map[t++].len = counter;
		counter = 0;
	}
	return (map);
}

static char	**ft_fill(char const *s, char **tab_2d, struct s_map *map, int n)
{
	int	t;

	t = 0;
	while (t < n)
	{
		tab_2d[t] = ft_substr(s, map[t].start, map[t].len);
		t++;
	}
	tab_2d[t] = 0;
	return (tab_2d);
}

char	**ft_split(char const *s, char c)
{	
	char			**tab_2d;
	struct s_map	*map;
	int				n;
	int				i;

	if (!s)
		return (0);
	i = 0;
	n = ft_pointer_counter(s, c);
	tab_2d = ft_calloc(n + 1, sizeof(char *));
	map = ft_calloc(n + 1, sizeof(struct s_map));
	if (map == NULL || tab_2d == NULL)
	{
		free(map);
		free(tab_2d);
		return (0);
	}
	map = ft_cut(map, s, c, i);
	tab_2d = ft_fill(s, tab_2d, map, n);
	free(map);
	return (tab_2d);
}
