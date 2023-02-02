
#include "miniRT_bonus.h"

char	**get_next_rgb(char **rgb, int *color)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (rgb[i][j] != ',')
	{
		j++;
	}
	tmp = ft_substr(*rgb, 0, j);
	*color = ft_atoi(tmp);
	*rgb = rgb[i];
	**rgb = rgb[i][j + 1];
	return (&*rgb);
}

int	is_rgb(int color)
{
	if (color > 255 || color < 0)
		return (0);
	return (1);
}

void	check_integer_format(t_minirt *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit_error(s, "Is not an integer", 1);
		i++;
	}
}

void	check_format_rgb(t_minirt *s, char *str)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			c++;
		else if (!ft_isdigit(str[i]))
			exit_error(s, "RGB error format.", 1);
	}
	if (c > 2)
		exit_error(s, "RGB error format.", 1);
}

t_color	get_rgb_str_to_color(t_minirt *s,  char *str, char *tmp)
{
	int		rgb[3];
	int		i[3];

	check_format_rgb(s, str);
	init_int_tab(rgb, -1, -1, -1);
	init_int_tab(i, 0, -1, 0);
	while (str[++i[1]])
	{
		i[0] = i[1];
		while (str[i[1]] && str[i[1]] != ',')
			i[1]++;
		tmp = ft_substr_gnl(str, i[0], i[1]);
		rgb[i[2]] = ft_atoi(tmp);
		i[2]++;
		free(tmp);
		if (str[i[1]] == 0)
			break ;
	}
	if (!is_rgb(rgb[0]) || !is_rgb(rgb[1]) || !is_rgb(rgb[2]))
		exit_error(0, "RGB out of range [0,255].", 1);
	return ((t_color) { rgb[0], rgb[1], rgb[2]});
}
