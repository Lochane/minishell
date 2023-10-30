/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:30:28 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 20:37:06 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst	*ft_new_lst(char *data)
{
	t_lst	*new;
	int		i;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	new->next = NULL;
	new->data = data;
	new->size = i;
	new->is_env = 1;
	return (new);
}

void	ft_clear_lst(t_lst **lst)
{
	t_lst	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

int	lst_size(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	print_list(t_lst *lst)
{
	while (lst)
	{
		printf("%s\n", lst->data);
		lst = lst->next;
	}
}

void	ft_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
