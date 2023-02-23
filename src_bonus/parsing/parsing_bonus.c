/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:03:04 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 13:16:51 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	exit_error(t_minirt *s, char *message, int opt)
{
	if (opt == 0)
	{
		ft_putstr_fd("\"", 2);
		if (s->argc > 1)
		{
			ft_putstr_fd(s->argv[1], 2);
			ft_putstr_fd("\" : ", 2);
		}
		perror(message);
	}
	else if (opt == 1)
	{
		ft_putstr_fd("Error\n\"", 2);
		if (s->argc > 1)
		{
			ft_putstr_fd(s->argv[1], 2);
			ft_putstr_fd("\" : ", 2);
		}
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	exit (EXIT_FAILURE);
}

void	check_directory(t_minirt *s)
{
	int		fd_params;

	fd_params = open(s->argv[1], O_DIRECTORY);
	if (fd_params > 2)
	{
		close(fd_params);
		exit_error(s, "is a directory", 1);
	}
}

// Check " ", "", "       "
void	check_void(t_minirt *s, size_t i)
{
	if (s->argc == 1)
		exit_error(s, "No scene selected.", 1);
	else if (s->argc > 2)
		exit_error(s, "Too much scenes selected.", 1);
	while (s->argv[1][i] == ' ')
		i++;
	if (i == ft_strlen(s->argv[1]))
		exit_error(s, "Empty name.", 1);
}

void	check_extension_rt(t_minirt *s)
{
	if (ft_strlen(s->argv[1]) < 4)
		exit_error(s, "Invalid file \".rt\".", 1);
	if (ft_strncmp(&s->argv[1][ft_strlen(s->argv[1]) - 3], ".rt", 4) != 0)
		exit_error(s, "Invalid extension.", 1);
}
