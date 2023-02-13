/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:56:52 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/13 19:56:56 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	print_list_id(void)
{
	printf("C / coordinates of the view point / 3d normalized orientation ");
	printf("vector / FOV\n");
	printf("A / ambient lighting ratio in range [0.0,1.0] / Color RGB\n");
	printf("L / coordinates of the light point / light brightness ratio in ");
	printf("range [0.0,1.0] / Color RGB\n");
	printf("sp / coordinates of the sphere center / diameter / Color RGB\n");
	printf("pl / coordinates / 3d normalized orientation vector / Color RGB\n");
	printf("cy / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
	printf("co / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
}

char	*ft_itof_print_next(int len, long tmp, char *str)
{
	len = ft_recursive_counter(tmp) + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (0);
	while (len)
	{
		len--;
		str[len] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	str[len] = '.';
	return (str);
}

char	*ft_itof_print(double n, char *str, char *integer, char *tmp_)
{
	long	tmp;

	if ((n < 0 && n > -1))
		integer = ft_strdup("-0");
	else
		integer = ft_itoa(n);
	n -= (int)n;
	tmp = n * 10;
	if (n < 0)
		tmp = -tmp;
	if (tmp == 0)
		tmp_ = ft_strjoin(integer, ".0");
	else
	{
		str = ft_itof_print_next(0, tmp, str);
		tmp_ = ft_strjoin(integer, str);
	}
	free(integer);
	free(str);
	return (tmp_);
}

void	print_rgb(t_color color, int fd)
{
	ft_putnbr_fd(color.r * 255, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(color.g * 255, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(color.b * 255, fd);
	ft_putstr_fd(" ", fd);
}

void	print_axis(t_vector vec, int fd)
{
	char	*tmp;

	tmp = ft_itof_print(vec.x, 0, 0, 0);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	ft_putstr_fd(",", fd);
	tmp = ft_itof_print(vec.y, 0, 0, 0);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	ft_putstr_fd(",", fd);
	tmp = ft_itof_print(vec.z, 0, 0, 0);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	ft_putstr_fd(" ", fd);
}
