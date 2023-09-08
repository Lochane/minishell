/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:20:26 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/08 16:58:17 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_insert_front(char *str, char *insert, int index)
{
	char	*tmp;
	int		i;
	int		strlen;

	strlen = ft_strlen(str) + ft_strlen(insert);
	tmp = malloc(sizeof(char) * (strlen + 1));
	tmp[strlen] = 0;
	ft_strlcpy(tmp, str, index + 2);
	ft_strlcpy(&tmp[index + 1], insert, ft_strlen(insert) + 1);
	ft_strlcpy(&tmp[index + ft_strlen(insert) + 1], &str[index + 1], \
		ft_strlen(&str[index]));
	return (tmp);
}

char	*ft_str_insert_back(char *str, char *insert, int index)
{
	char	*tmp;
	int		i;
	int		strlen;

	strlen = ft_strlen(str) + ft_strlen(insert);
	tmp = malloc(sizeof(char) * (strlen + 1));
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
		tmp = ft_strdup(tmp2);
	}
	if (space_count > 1)
	{
		ft_memmove(tmp + (index + 1), tmp + j_index, ft_strlen(tmp));
		tab = ft_strdup(tmp);
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
		tmp = ft_strdup(tmp2);
	}
	if (space_count > 1)
	{
		ft_memmove(tmp + found_space(tmp, 0), tmp + index, ft_strlen(tmp));
		tab = ft_strdup(tmp);
	}
	return (tmp);
}
