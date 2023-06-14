/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:28:49 by lochane           #+#    #+#             */
/*   Updated: 2023/06/14 12:12:28 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_simple_cmd	*lstnew_simple_cmd(char **content, int size)
{
	t_simple_cmd	*liste;
	int	i;

	i = 0;
	liste = malloc(sizeof(t_simple_cmd));
	liste->str = malloc(sizeof(char **) * (size + 1));
	if (!liste)
		return (NULL);
	while (content[i])
	{
		liste->str[i] = content[i];
		i++;
	}
	liste->next = NULL;
	liste->prev = NULL;
	return (liste);
}

void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*temp;

	if (!lst || !new)
		return ;
	temp = *lst;
	if (lst && (*lst))
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	else
	*lst = new;
}

void	go_prev_simple_cmd(t_simple_cmd **lst)
{
	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
}