/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:20:26 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/11 20:08:50 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_str_insert_front(char *str, char *insert, int index)
{
	char	*tmp;
	int		strlen;
	int		size;
	int		str_size;

	strlen = ft_strlen(str) + ft_strlen(insert);
	tmp = malloc(sizeof(char) * (strlen + 1));
	if (!tmp)
		return (fail_malloc(), NULL);
	size = ft_strlen(insert);
	str_size = ft_strlen(&str[index]);
	tmp[strlen] = 0;
	ft_strlcpy(tmp, str, index + 2);
	ft_strlcpy(&tmp[index + 1], insert, size + 1);
	ft_strlcpy(&tmp[index + size + 1], &str[index + 1], \
		str_size);
	return (tmp);
}

char	*ft_str_insert_back(char *str, char *insert, int index)
{
	char	*tmp;
	int		strlen;

	strlen = ft_strlen(str) + ft_strlen(insert);
	tmp = malloc(sizeof(char) * (strlen + 1));
	if (!tmp)
		return (fail_malloc(), NULL);
	tmp[strlen] = 0;
	ft_strlcpy(tmp, str, index + 1);
	ft_strlcpy(&tmp[index], insert, ft_strlen(insert) + 1);
	ft_strlcpy(&tmp[index + ft_strlen(insert)], &str[index], \
		ft_strlen(&str[index]) + 1);
	return (tmp);
}

char	*manage_space_back(int index, char *tab, int space_count, int j_index)
{
	char	*tmp;
	char	*tmp2;

	tmp = tab;
	if (space_count == 0)
	{
		tmp2 = ft_str_insert_back(tmp, " ", index);
		if (!tmp2)
			return (NULL);
		tmp = ft_strdup(tmp2);
		if (!tmp)
			return (free(tmp2), fail_malloc(), NULL);
		free(tmp2);
	}
	if (space_count > 1)
	{
		ft_memmove(tmp + (index + 1), tmp + j_index, ft_strlen(tmp));
		free(tab);
		tab = ft_strdup(tmp);
		if (!tab)
			return (free(tmp), fail_malloc(), NULL);
	}
	return (tmp);
}

char	*manage_space_front(int index, char *tab, int space_count)
{
	char	*tmp;
	char	*tmp2;

	tmp = tab;
	if (space_count == 0)
	{
		tmp2 = ft_str_insert_front(tmp, " ", index);
		if (!tmp2)
			return (NULL);
		tmp = ft_strdup(tmp2);
		if (!tmp)
			return (fail_malloc(), NULL);
	}
	if (space_count > 1)
	{
		ft_memmove(tmp + found_space(tmp, 0), tmp + index, ft_strlen(tmp));
		tab = ft_strdup(tmp);
		if (!tab)
			return (fail_malloc(), NULL);
	}
	return (tmp);
}
