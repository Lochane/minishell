/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/03 14:38:11 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free_tab(char **res, size_t i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (NULL);
}

void	print_tab(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	initialise_cmd(t_cmd *cmd)
{
		cmd->arg = NULL;
		cmd->out = NULL;
		cmd->in = NULL;
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