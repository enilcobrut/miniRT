/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:48:35 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 14:27:30 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	nb_arg_tab(char **tab)
{
	int	nb;

	nb = 0;
	while (tab[nb])
		nb++;
	return (nb);
}

int	is_void(char *str, int end)
{
	int	i;

	if (end == -1)
		end = ft_strlen(str);
	i = 0;
	while (str[i] && i < end)
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_float_atof(t_minirt *s, char *str, int i)
{
	if (ft_strlen(str) > 10)
		exit_error(s, "Error float format. > 10", 1);
	if (str[ft_strlen(str) - 1] == '.')
		exit_error(s, "Error float format.", 1);
	while (str[i])
	{
		if (str[0] == '.')
			exit_error(s, "Error float format.", 1);
		else if (str[i] == '.')
		{
			i++;
			break ;
		}
		else if (str[i] != '-' && !ft_isdigit(str[i]))
			exit_error(s, "Error float format.", 1);
		i++;
	}
	return (i);
}

double	ft_atof(t_minirt *s, char *str, double res, double res2)
{
	int		len;
	int		i;

	i = check_float_atof(s, str, 0);
	res = ft_atoi(str);
	len = i;
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		else if (str[i] != '-' && !ft_isdigit(str[i]))
			exit_error(s, "Error float format.", 1);
		i++;
	}
	i = len;
	res2 = (double)ft_atoi(&str[i]);
	len = ft_strlen(&str[i]);
	while (len--)
		res2 /= 10;
	if (str[0] != '-')
		return (res + res2);
	else
		return (res + -res2);
}

void	init_int_tab(int *i, int a, int b, int c)
{
	i[0] = a;
	i[1] = b;
	i[2] = c;
}
