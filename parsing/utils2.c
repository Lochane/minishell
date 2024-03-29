/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:50:46 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 20:28:22 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*do_space_front(int *i, char *tab, int space_count)
{
	tab = manage_space_front(i[0], tab, space_count);
	if (i[0] > (int)ft_strlen(tab))
		i[0] = ft_strlen(tab);
	return (tab);
}

void	free_redirection(t_dir *redir)
{
	t_dir	*tmp_dir;

	while (redir)
	{
		free(redir->file);
		tmp_dir = redir->next;
		if (redir->fd != -1)
			close(redir->fd);
		free(redir);
		redir = tmp_dir;
	}
}

void	manage_data(t_data *data, int allow)
{
	t_cmd	*tmp;

	if (allow == 0)
	{
		data->args = NULL;
		data->cmd = NULL;
	}
	else
	{
		while (data->cmd)
		{
			free_redirection(data->cmd->redirection);
			ft_free_tab(data->cmd->arg, tab_size(data->cmd->arg));
			free(data->cmd->cmd);
			tmp = data->cmd->next;
			free(data->cmd);
			data->cmd = tmp;
		}
		free(data->args);
		data->args = NULL;
		data->cmd = NULL;
	}
}

void	remove_space(char *tab)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(tab);
	while (tab[i])
	{
		if (tab[i] == ' ' && tab[i + 1] == ' ')
		{
			ft_memmove(&tab[i], &tab[i + 1], len - i);
			j = ft_strlen(tab);
			while (--len > j)
				tab[len] = 0;
		}
		else
			i++;
	}
}
