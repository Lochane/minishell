/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:53:12 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:57:28 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*s;
	char		*dst;

	i = 0;
	s = src;
	dst = (char *)dest;
	if (s > dst)
	{
		while (i < n)
		{
			dst[i] = s[i];
			i++;
		}
	}
	else if (s < dst)
	{
		i = n;
		while (i > 0)
		{
			dst[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dst);
}
