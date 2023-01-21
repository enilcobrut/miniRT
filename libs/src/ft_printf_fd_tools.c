/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:49:18 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/25 13:33:11 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_putchar_counter(char c, int fd, int *count)
{
	write(fd, &c, 1);
	*count += 1;
}

void	ft_putstr_counter(char *s, int fd, int *count)
{
	int	i;

	i = 0;
	if (!s)
		ft_putstr_counter("(null)", fd, count);
	else
	{
		while (s[i])
		{
			ft_putchar_counter(s[i], fd, count);
			i++;
		}
	}
}

void	ft_putnbr_counter_fd(long n, int fd, int *count)
{
	if (n < 0)
	{
		n = -n;
		ft_putchar_counter('-', fd, count);
		ft_putnbr_counter_fd(n, fd, count);
	}
	else if (n >= 10)
	{
		ft_putnbr_counter_fd((n / 10), fd, count);
		ft_putnbr_counter_fd((n % 10), fd, count);
	}
	else
		ft_putchar_counter(n + '0', fd, count);
}

void	ft_hexa(unsigned long num, char type, int fd, int *count)
{
	char	*hexa_set;
	char	*tmp;
	char	buffer[50];

	tmp = &buffer[49];
	hexa_set = "0123456789ABCDEF";
	*tmp = 0;
	if (num == 0)
		tmp = "0";
	while (num != '\0')
	{
		if (type == 'X')
			*--tmp = hexa_set[num % 16];
		if (type == 'x')
			*--tmp = ft_tolower(hexa_set[num % 16]);
		num /= 16;
	}
	ft_putstr_counter(tmp, fd, count);
}
