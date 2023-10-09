/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 14:30:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_arg(t_cmd *cmd, char **tab)
{
	cmd->arg = malloc(sizeof(char *) * (tab_size(tab) + 1));
	if (!cmd->arg)
		return (0);
	return (1);
}

void	*ft_free_tab(char **res, size_t i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (NULL);
}

void	add_back(t_cmd *lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst || !new)
		return ;
	temp = lst;
	if (lst)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
	lst = new;
}

void	add_back_dir(t_dir **lst, t_dir *new)
{
	t_dir	*temp;

	if (!lst || !new)
		return ;
	temp = *lst;
	if (lst && (*lst))
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
	*lst = new;
}

t_dir	*init_dir(char *file)
{
	t_dir	*new;

	new = malloc(sizeof(t_dir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	new->token = 0;
	new->next = NULL;
	new->fd = -1;
	return (new);
}
