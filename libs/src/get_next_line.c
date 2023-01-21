/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:05 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:12 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stock;
	int			count;
	char		buf[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 0 || fd < 0)
		return (0);
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		put_buf_in_stock(&stock, buf);
		if (search_endl_in(stock) != -1)
			return (get_line(&stock));
		count = read(fd, buf, BUFFER_SIZE);
	}
	return (get_line(&stock));
}

void	put_buf_in_stock(char **stock, char *buf)
{
	static char	*new_stock;
	int			s;
	int			b;
	int			len;

	s = 0;
	b = 0;
	len = ft_strlen_gnl(*stock) + ft_strlen_gnl(buf) + 1;
	new_stock = ft_calloc(len, sizeof(char));
	if (new_stock == NULL)
		return ;
	while (*stock && (*stock)[s])
	{
		*(new_stock + s) = *(*stock + s);
		s++;
	}
	while (buf[b])
	{
		new_stock[s + b] = buf[b];
		b++;
	}
	new_stock[s + b] = 0;
	free(*stock);
	*stock = new_stock;
}

char	*get_line(char **stock)
{
	int		end_line;
	char	*line;
	char	*new_stock;

	if (!*stock)
		return (0);
	end_line = search_endl_in(*stock);
	if (end_line != -1)
	{
		line = ft_substr_gnl(*stock, 0, end_line + 1);
		new_stock = ft_substr_gnl(*stock, end_line + 1, ft_strlen_gnl(*stock));
		free(*stock);
		*stock = new_stock;
	}
	else
	{
		line = ft_substr_gnl(*stock, 0, ft_strlen_gnl(*stock));
		free(*stock);
		*stock = NULL;
	}
	return (line);
}
