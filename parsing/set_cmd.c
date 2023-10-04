/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/09/30 13:40:23 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redirection(char **tab, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
		{
			if (!manage_redirection(tab[i], tab[i + 1], cmd))
				return (0);
			i += 2;
		}
		else
			i++;
	}
	return (1);
}

int	get_cmd(char **tab, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
			i += 2;
		else
		{
			cmd->cmd = ft_strdup(tab[i]);
			if (!cmd->cmd)
				return (0);
			break ;
		}
	}
	return (1);
}

int	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;

	i = 0;
	i = find_index(i, tab, 0);
	j = 0;
	while (tab && tab[i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
			i = find_index(i, tab, 1);
		else
		{
			if (!cmd->arg)
			{
				cmd->arg = malloc(sizeof(char *) * (tab_size(tab) + 1));
				if (!cmd->arg)
					return (0);
			}
			cmd->arg[j++] = ft_strdup(tab[i++]);
			if (!cmd->arg)
				return (0);
		}
	}
	if (cmd->arg)
		cmd->arg[j] = NULL;
	return (1);
}

int	tri_cmd(char *tab, t_cmd *cmd)
{
	char	**tmp;

	tab = check_space_front(tab);
	tab = check_space_back(tab);
	tmp = ft_split_shell(tab, ' ');
	if (!tmp)
		return (0);
	if (!get_redirection(tmp, cmd))
		return (0);
	if (!get_cmd(tmp, cmd))
		return (0);
	if (tab[1])
	{
		if (!get_arg(tmp, cmd))
			return (0);
	}
	ft_free_tab(tmp, tab_size(tmp));
	return (1);
}

int	set_cmd(t_data *data)
{
	char	**tmp;
	t_cmd	*lst_tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lst_tmp = NULL;
	tmp = ft_split_shell(data->args, '|');
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		lst_tmp = init_cmd();
		if (!tri_cmd(tmp[i], lst_tmp))
			return (0);
		if (i == 0)
			data->cmd = lst_tmp;
		else
			add_back(data->cmd, lst_tmp);
		lst_tmp = lst_tmp->next;
		i++;
	}
	ft_free_tab(tmp, tab_size(tmp));
	return (1);
}