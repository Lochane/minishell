/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:43:37 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:56:35 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long int n)
{
	long int	i;

	i = 0;
	if (n < 0)
		n = n * (-1);
	else if (n == 0)
		i++;
	while (n > 0)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

static char	*ft_nbr(long int c, char *r, int size)
{
	int	i;

	i = size - 1;
	while (c > 0)
	{
		r[i] = c % 10 + 48;
		c = c / 10;
		i--;
	}
	r[size] = '\0';
	return (r);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			size;
	long int	i;

	i = n;
	size = count(n);
	if (n < 0)
		size += 1;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (i < 0)
	{
		res[0] = '-';
		i = i * (-1);
	}
	else if (i == 0)
		res[0] = '0';
	ft_nbr(i, res, size);
	return (res);
}
