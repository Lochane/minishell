/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:22:37 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:57:36 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	make_p(long unsigned int nb)
{
	int	i;

	i = 0;
	if (!nb)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	i += ft_putstr_printf("0x", 1);
	i += ft_make_this_p(nb);
	return (i);
}

static int	make_it_hexa(unsigned int n, int c)
{
	unsigned int	i;

	i = 0;
	if (n >= 16)
	{
		i += make_it_hexa((n / 16), c);
		i += make_it_hexa((n % 16), c);
	}
	else
	{
		if (n < 10)
		{
			i += ft_putnbr_printf(n + 0, 1);
		}
		else
		{
			if (c == 'x')
				i += ft_putchar_printf(n + 'a' - 10, 1);
			if (c == 'X')
				i += ft_putchar_printf(n + 'A' - 10, 1);
		}
	}
	return (i);
}

static int	make_u(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 9)
		i += ft_putchar_printf(n + 48, 1);
	else
	{
		i += ft_putnbr_printf(n / 10, 1);
		i += ft_putnbr_printf(n % 10, 1);
	}
	return (i);
}

static int	what_to_print(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_printf(va_arg(arg, int), 1);
	if (c == 's')
		count += ft_putstr_printf(va_arg(arg, char *), 1);
	if (c == 'p')
		count += make_p(va_arg(arg, long unsigned int));
	if (c == 'd')
		count += ft_putnbr_printf(va_arg(arg, int), 1);
	if (c == 'i')
		count += ft_putnbr_printf(va_arg(arg, int), 1);
	if (c == 'u')
		count += make_u(va_arg(arg, unsigned int));
	if (c == 'x')
		count += make_it_hexa(va_arg(arg, unsigned int), 'x');
	if (c == 'X')
		count += make_it_hexa(va_arg(arg, unsigned int), 'X');
	if (c == '%')
		count += ft_putchar_printf('%', 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	const char	*save;
	va_list		arg;

	va_start(arg, format);
	i = 0;
	count = 0;
	save = format;
	while (save[i])
	{
		if (save[i] == '%')
		{
			i++;
			count += what_to_print(save[i], arg);
		}
		else
			count += ft_putchar_printf(save[i], 1);
		i++;
	}
	va_end(arg);
	return (count);
}
