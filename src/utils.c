/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/19 16:07:27 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

char	*ft_strjoin_shell(char const *s1, char const *s2, int j)
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
	res = malloc(sizeof(char) * s1_size + s2_size + (1 + j));
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