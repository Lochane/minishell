/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/07/03 12:34:29 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

int	lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;
	int		size;

	i = 1;
	j = 0;
	size = tab_size(tab);
	cmd->out = NULL;
	cmd->in = NULL;
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
				cmd->arg[size - 1] = NULL;
			}
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

	check_space_before(tab);
	check_space_after(tab);
	tmp = ft_split_shell(tab, ' ');
	cmd->cmd = ft_strdup(tmp[0]);
	if (tab[1])
	{
		cmd->arg = NULL;
		get_arg(tmp, cmd);
		if (cmd->arg)
			print_tab(cmd->arg);
	}
	free(tmp);
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
	lst_tmp = NULL;
	data->cmd = malloc(sizeof(t_cmd));
	tmp = ft_split(data->args, '|');
	while (tmp[i])
	{
		tri_cmd(tmp[i], data->cmd);
		if (!lst_tmp)
			lst_tmp = data->cmd;
		i++;
		data->cmd = data->cmd->next;
	}
	data->cmd = lst_tmp;
	free(tmp);
	printf("%d\n",lstsize(data->cmd));
}
