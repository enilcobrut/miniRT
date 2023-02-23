/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_axis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:50:38 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 12:23:03 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_axis_format(t_minirt *s, char *axis, char *tmp)
{
	int		i[3];

	init_int_tab(i, -1, 0, 0);
	while (axis[++i[0]])
	{
		if (axis[i[0]] == ',')
		{
			i[1]++;
			tmp = ft_substr(axis, 0, i[0]);
			check_float_format(s, tmp);
			ft_free(&tmp);
			axis = &axis[i[0]] + 1;
			i[0] = 0;
		}
		else if (axis[i[0]] != '.' && axis[i[0]] != '-'
			&& !ft_isdigit(axis[i[0]]))
			exit_error(s, "Axis format aren't compliant", 1);
	}
	tmp = ft_substr(axis, 0, i[0]);
	check_float_format(s, tmp);
	ft_free(&tmp);
	i[1]++;
	if (i[1] > 3)
		exit_error(s, "Axis format aren't compliant", 1);
}

void	check_float_format(t_minirt *s, char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		else if (!ft_isdigit(str[i]))
			exit_error(s, "Float error format.", 1);
		i++;
	}
	if (dot > 1 || str[0] == '.' || str[ft_strlen(str) - 1] == '.')
		exit_error(s, "Float error format.", 1);
}

void	get_tab_to_point(t_minirt *s, t_vector *p)
{
	p->x = s->f[0];
	p->y = s->f[1];
	p->z = s->f[2];
}

void	get_axis(t_minirt *s, t_vector *p, char *str, char *tmp)
{
	int	i[3];

	check_axis_format(s, str, 0);
	init_int_tab(i, 0, -1, 0);
	while (str[++i[1]])
	{
		i[0] = i[1];
		while (str[i[1]] && str[i[1]] != ',')
			i[1]++;
		tmp = ft_substr_gnl(str, i[0], i[1]);
		s->f[i[2]] = ft_atof(s, tmp, 0, 0);
		i[2]++;
		ft_free(&tmp);
		if (str[i[1]] == 0)
			break ;
	}
	get_tab_to_point(s, p);
}

void	check_vector_range(t_minirt *s, t_vector *p)
{
	if (p->x > 1 || p->x < -1)
		exit_error(s, "3d NO vector isn't in range [-1,1].", 1);
	if (p->y > 1 || p->y < -1)
		exit_error(s, "3d NO vector isn't in range [-1,1].", 1);
	if (p->z > 1 || p->z < -1)
		exit_error(s, "3d NO vector isn't in range [-1,1].", 1);
}
