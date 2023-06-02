/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:03:04 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:58:09 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checkword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{	
			count++;
			while (s[i] && c != s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_checkletter(char const *s, char c, size_t i)
{
	size_t	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
			count++;
			i++;
	}
	return (count);
}

static void	*ft_free(char **res, size_t i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	letter_count;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	res = (char **)malloc(sizeof(char *) * (ft_checkword(s, c) + 1));
	if (!res)
		return (NULL);
	while (++j < ft_checkword(s, c))
	{
		while (s[i] == c)
			i++;
		letter_count = ft_checkletter(s, c, i);
		res[j] = ft_substr(s, i, letter_count);
		if (!res[j])
			return (ft_free(res, j));
		i += letter_count;
	}
	res[j] = 0;
	return (res);
}
