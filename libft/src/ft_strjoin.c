/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:36:47 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:58:26 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		s1_size;
	int		s2_size;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	res = malloc(sizeof(char) * (s1_size + s2_size) + 1);
	if (!res)
		return (0);
	ft_memcpy(res, s1, s1_size);
	while (s2[i])
	{
		res[s1_size + i] = s2[i];
		i++;
	}
	res[s1_size + i] = '\0';
	return (res);
}
