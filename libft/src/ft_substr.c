/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:49:37 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = start;
	if (start > ft_strlen(s))
		res = malloc(sizeof(char));
	else if (len < ft_strlen(s + j))
		res = malloc(sizeof(char) * (len + 1));
	else
		res = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (!res)
		return (NULL);
	while (!(start > ft_strlen(s)) && s[j] && i < len)
	{
		res[i] = s[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
