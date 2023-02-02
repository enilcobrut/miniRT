
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
	if (LEAKS == 1)
		system("leaks miniRT");
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
	while (s->argv[1][i] && s->argv[1][i] == ' ')
	{
		if (s->argv[1][i] != ' ')
			i = -1;
		i++;
	}
	if (i == ft_strlen(s->argv[1]))
		exit_error(s, "Empty name.", 1);
}

void	check_extension_rt(t_minirt *s)
{
	size_t	start;

	start = ft_strlen(s->argv[1]);
	while (start > 0)
	{
		if (s->argv[1][start - 1] == '/')
			break ;
		start--;
	}
	if (ft_strncmp(&s->argv[1][ft_strlen(s->argv[1]) - 3], ".rt", 4) != 0
		|| !ft_strncmp(s->argv[1], ".rt", 4))
		exit_error(s, "Invalid extension.", 1);
	if (ft_strlen(s->argv[1]) - 3 - start == 0)
		exit_error(s, "Invalid file \".rt\".", 1);
}
