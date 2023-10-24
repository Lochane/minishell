/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:20:26 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/24 17:44:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_space(char *tab, char *save_tab)
{
	char	*tmp_tab2;
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == '\t' || tab[i] == '\n' || tab[i] == '\n' || \
				tab[i] == '\v' || tab[i] == '\f' || tab[i] == '\r')
			tab[i] = ' ';
		i++;
	}
	tab = check_space_front(tab);
	if (!tab)
		return (0);
	tmp_tab2 = tab;
	tab = check_space_back(tab);
	if (!tab)
		return (0);
	if (tab != tmp_tab2 && tmp_tab2 != save_tab)
		free(tmp_tab2);
	return (tab);
}

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
		ft_memmove(tmp + (index + 1), tmp + j_index, \
			ft_strlen(tmp + j_index - 1));
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
		free(tmp2);
		if (!tmp)
			return (fail_malloc(), NULL);
	}
	if (space_count > 1)
	{
		ft_memmove(tmp + found_space(tmp, 0), tmp + index, \
			ft_strlen(tmp + index));
		tmp[ft_strlen(tmp) - index + 3] = '\0';
	}
	return (tmp);
}
