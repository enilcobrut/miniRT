/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:51:04 by flemaitr          #+#    #+#             */
/*   Updated: 2022/04/25 12:51:31 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <unistd.h>
# include <stdarg.h>
# include <assert.h>
# include "libft.h"

int		ft_printf_fd(int fd, const char *format, ...);
void	ft_select(char f, va_list arg, int fd, int *count);
void	ft_putchar_counter(char c, int fd, int *count);
void	ft_putstr_counter(char *s, int fd, int *count);
void	ft_putnbr_counter_fd(long n, int fd, int *count);
void	ft_hexa(unsigned long num, char type, int fd, int *count);

#endif
