/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/19 19:23:00 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

void	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;

	i = 1;
	j = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<')
			i = manage_in(tab[i], tab[i + 1], cmd, i);
		else if (tab[i][0] == '>')
			i = manage_out(tab[i], tab[i + 1], cmd, i);
		else
		{
			cmd->arg[j] = ft_strdup(tab[i]);
			j++;
			i++;
		}
	}
}

// TODO free tmp

void	tri_cmd(char *tab, t_cmd *cmd)
{
	char	**tmp;
	int		size;

	check_space_before(tab);
	check_space_after(tab);
	tmp = ft_split(tab, ' ');
	size = tab_size(tmp);
	cmd->cmd = ft_strdup(tmp[0]);
	if (tab[1])
	{
		cmd->arg = malloc(sizeof(char **) * size - 1);
		get_arg(tmp, cmd);
	}
}

// TODO free tmp

void	set_cmd(t_data *data)
{
	char	**tmp;
	t_cmd	*lst_tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_split(data->args, '|');
	while (tmp[i])
	{
		data->cmd = malloc(sizeof(t_cmd));
		tri_cmd(tmp[i], data->cmd);
		i++;
		data->cmd = data->cmd->next;
	}
}