
#include "miniRT_bonus.h"

void	get_params_loop(t_minirt *s, char *tmp, int fd_params)
{
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd_params);
		if (tmp && tmp[0])
		{
			if (tmp[ft_strlen(tmp) - 1] == '\n')
				tmp[ft_strlen(tmp) - 1] = 0;
			if (ft_strncmp(tmp, "\n", 2) && !is_void(tmp, ft_strlen(tmp))
				&& ft_strncmp(tmp, "#", 1))
				ft_lstadd_back(&s->params, ft_lstnew(ft_split(tmp, ' ')));
		}
	}
	free(tmp);
	close(fd_params);
}

void	get_params(t_minirt *s)
{
	int		fd_params;
	char	*tmp;

	tmp = NULL;
	fd_params = open(s->argv[1], O_RDONLY);
	if (fd_params == -1)
		exit_error(s, 0, 0);
	tmp = get_next_line(fd_params);
	if (tmp && tmp[0])
	{
		if (tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		if (ft_strncmp(tmp, "\n", 2) && !is_void(tmp, ft_strlen(tmp))
			&& ft_strncmp(tmp, "#", 1))
			ft_lstadd_back(&s->params, ft_lstnew(ft_split(tmp, ' ')));
	}
	get_params_loop(s, tmp, fd_params);
	printf("%d\n", ft_lstsize(s->params));
}
