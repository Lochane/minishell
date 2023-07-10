/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/07/10 14:24:37 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

void	found_cmd(char **tab, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<')
			i = manage_in(tab[i], tab[i + 1], cmd, i);
		else if (tab[i][0] == '>')
			i = manage_out(tab[i], tab[i + 1], cmd, i);
		else
		{
			cmd->cmd = ft_strdup(tab[i]);
			break ;
		}
	}
}

void	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;
	int		size;

	i = 1;
	j = 0;
	size = tab_size(tab);
	while (tab[i])
	{
		if (tab[i][0] == '<')
			i = manage_in(tab[i], tab[i + 1], cmd, i);
		else if (tab[i][0] == '>')
			i = manage_out(tab[i], tab[i + 1], cmd, i);
		else
		{
			if (!cmd->arg)
			{
				cmd->arg = malloc(sizeof(char *) * size);
				if (!cmd->arg)
					return ;
				cmd->arg[size - 1] = NULL;
			}
			cmd->arg[j++] = ft_strdup(tab[i++]);
		}
	}
}

void	tri_cmd(char *tab, t_cmd *cmd)
{
	char	**tmp;

	check_space_before(tab);
	check_space_after(tab);
	tmp = ft_split_shell(tab, ' ');
	print_tab(tmp);
	found_cmd(tmp, cmd);
	if (tab[1])
	{
		get_arg(tmp, cmd);
		if (cmd->arg)
			print_tab(cmd->arg);
	}
	free(tmp);
}




void	set_cmd(t_data *data)
{
	char	**tmp;
	t_cmd	*lst_tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lst_tmp = NULL;
	tmp = ft_split(data->args, '|');
	while (tmp[i])
	{
		lst_tmp = init_cmd();
		tri_cmd(tmp[i], lst_tmp);
		if (i == 0)
			data->cmd = lst_tmp;
		else
			add_back(data->cmd, lst_tmp);
		lst_tmp = lst_tmp->next;
		i++;
	}
	free(tmp);
}
