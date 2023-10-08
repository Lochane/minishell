/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/08 22:49:27 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int remove_lst(t_lst **lst, char *name)
{
	(void) lst;
	t_lst	*tmp;
	t_lst	*prev;

	if (!*lst)
		return (0);
	prev = *lst;
	ft_get_env(name, ft_strlen(name), *lst, &tmp);
	if (!tmp)
		return (0);
	if (tmp == *lst)
	{
		prev = prev->next;
		free(tmp->data);
		free(tmp);
		*lst = prev;
		return (1);
	}
	while (prev && prev->next != tmp)
		prev = prev->next;
	prev->next = tmp->next;
	free(tmp->data);
	free(tmp);
	return (1);
}

int	do_unset(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int	i;
	
	(void) cmd;
	(void) fd;
	(void) data;
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			remove_lst(&data->env, cmd->arg[i]);
			i++;
		}
	}
	return (0);
}