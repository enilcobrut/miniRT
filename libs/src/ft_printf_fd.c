/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:48:31 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/25 13:31:37 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_select(char f, va_list arg, int fd, int *count)
{
	if (f == '%')
		ft_putchar_counter('%', fd, count);
	else if (f == 's')
		ft_putstr_counter(va_arg(arg, char *), fd, count);
	else if (f == 'c')
		ft_putchar_counter((char)va_arg(arg, int), fd, count);
	else if (f == 'p')
	{
		ft_putstr_counter("0x", fd, count);
		ft_hexa(va_arg(arg, unsigned long), 'x', fd, count);
	}
	else if (f == 'x' || f == 'X')
		ft_hexa(va_arg(arg, unsigned int), f, fd, count);
	else if (f == 'i' || f == 'd')
		ft_putnbr_counter_fd(va_arg(arg, int), fd, count);
	else if (f == 'u')
		ft_putnbr_counter_fd(va_arg(arg, unsigned int), fd, count);
	else
		return ;
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	arg;
	int		*count;
	int		written_characters;
	char	f;

	va_start(arg, format);
	written_characters = 0;
	f = *format;
	count = &written_characters;
	while (*format)
	{
		f = *format;
		if (f != '%')
			ft_putchar_counter((f = *format), fd, count);
		if (f == '%')
		{
			format++;
			ft_select((f = *format), arg, fd, count);
		}
		format++;
	}
	va_end(arg);
	return (written_characters);
}
