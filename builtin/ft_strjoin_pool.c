/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:39:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 16:26:27 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
	{
		i++;
	}
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static int	ultimate_length(int size, char **strs, char *sep)
{
	int	i;
	int	final_size;
	int	j;

	i = 0;
	final_size = 0;
	if (size == 0)
		return (0);
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
		{
			final_size++;
			j++;
		}
	i++;
	}
	final_size = final_size + ft_strlen(sep) * (size - 1);
	return (final_size);
}

char	*ft_strjoin_pool(int size, char **strs, char *sep, int new_line)
{
	int		index;
	int		ultimate_size;
	char	*tab;

	index = 0;
	ultimate_size = ultimate_length(size, strs, sep) + (new_line == 0);
	tab = malloc((ultimate_size + 1) * sizeof(char));
	if (!tab)
		return (fail_malloc(), NULL);
	tab[index] = '\0';
	while (index < size)
	{
		ft_strcat(tab, strs[index]);
		if (index < size - 1)
			ft_strcat(tab, sep);
	index++;
	}
	// printf("ultimate = %d\n, bool = %d\n", ultimate_size, bool);
	if (new_line == 0)
		tab[ultimate_size - 1] = '\n';
	tab[ultimate_size] = '\0';
	return (tab);
}
