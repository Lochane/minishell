/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:32:36 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:57:57 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_printf(int n, int fd)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i += ft_putchar_printf('-', fd);
		i += ft_putchar_printf('2', fd);
		i += ft_putnbr_printf(147483648, fd);
	}
	else if (n >= 0 && n <= 9)
		i += ft_putchar_printf(n + 48, fd);
	else if (n < 0)
	{
		i += ft_putchar_printf('-', fd);
		i += ft_putnbr_printf(n *(-1), fd);
	}
	else
	{
		i += ft_putnbr_printf(n / 10, fd);
		i += ft_putnbr_printf(n % 10, fd);
	}
	return (i);
}
