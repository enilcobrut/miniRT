/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_back_up_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:50:05 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 19:15:16 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	export_file_save(t_minirt *s, int opt)
{
	int		fd;
	char	*tmp;

	tmp = NULL;
	if (opt == 1)
	{
		tmp = ft_strjoin(s->argv[1], "_save");
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		free(tmp);
	}
	else
		fd = open(s->argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write_params(s, fd);
	close(fd);
}

void	print_atof(double n, int fd)
{
	char	*tmp;

	tmp = ft_itof(n);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}
