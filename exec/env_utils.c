/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:30:39 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 20:39:44 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst	*tab_to_list(char **tab)
{
	int		i;
	t_lst	*lst;
	t_lst	*new;

	i = 0;
	lst = NULL;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		new = ft_new_lst(ft_strdup(tab[i]));
		if (!new)
			return (ft_clear_lst(&lst), lst);
		ft_add_back(&lst, new);
		i++;
	}
	return (lst);
}

char	**lst_to_tab(t_lst *lst)
{
	int		size;
	char	**tab;
	int		i;

	i = 0;
	size = lst_size(lst);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (lst)
	{
		tab[i] = lst->data;
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
