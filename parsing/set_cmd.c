/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/10/26 16:38:35 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_redirection(char **tab, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
		{
			if (!tab[i + 1])
				return (0);
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
				return (fail_malloc(), 0);
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
				if (!fill_arg(cmd, tab))
					return (0);
			}
			cmd->arg[j++] = ft_strdup(tab[i++]);
			if (!cmd->arg)
				return (fail_malloc(), 0);
		}
	}
	if (cmd->arg)
		cmd->arg[j] = NULL;
	return (1);
}

int	tri_cmd(char *tab, t_cmd *cmd)
{
	char	**tmp;
	char	*save_tab;
	char	*tmp_tab;

	save_tab = tab;
	tab = trim_space(tab, save_tab);
	tmp_tab = tab;
	tmp = ft_split_shell(tab, ' ');
	if (!tmp)
		return (fail_malloc(), 0);
	if (!get_redirection(tmp, cmd))
		return (ft_free_tab(tmp, tab_size(tmp)), 0);
	if (!get_cmd(tmp, cmd))
		return (ft_free_tab(tmp, tab_size(tmp)), 0);
	if (tab[1])
	{
		if (!get_arg(tmp, cmd))
			return (ft_free_tab(tmp, tab_size(tmp)), 0);
	}
	ft_free_tab(tmp, tab_size(tmp));
	if (tmp_tab != save_tab)
		free(tab);
	return (1);
}

int	set_cmd(t_data *data)
{
	char	**tmp;
	t_cmd	*lst_tmp;
	int		i;

	i = 0;
	lst_tmp = NULL;
	tmp = split_and_check(data);
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		lst_tmp = init_cmd();
		if (!lst_tmp)
			return (fail_malloc(), 0);
		if (!tri_cmd(tmp[i], lst_tmp))
			return (ft_free_tab(tmp, tab_size(tmp)), free(lst_tmp), 0);
		if (i == 0)
			data->cmd = lst_tmp;
		else
			add_back(data->cmd, lst_tmp);
		i++;
	}
	ft_free_tab(tmp, tab_size(tmp));
	return (1);
}
