/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/04 22:47:39 by madaguen         ###   ########.fr       */
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
	while (prev && prev->next != tmp)
		prev = prev->next;
	prev->next = tmp->next;
	free(tmp->data);
	free(tmp);
	return (1);
}

int	do_unset(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	(void) data;
	int	i;

	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			remove_lst(&data->env, cmd->arg[i]);//a faire en boucle tant au'il y a des arg
			i++;
		}
	}
	return (0);
}