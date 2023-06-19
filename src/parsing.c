/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/19 16:31:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

int	found_space(char *tab, int allow)
{
	int	i;

	i = 0;
	while (tab[i] != ' ' && allow == 0)
		i++;
	return (i);
}

void	check_space_before(char *tab)
{
	int	i;
	int	j;
	int	space_count;

	i = ft_strlen(tab);
	while (tab[--i])
	{
		space_count = 0;
		if (tab[i] == '>' || tab[i] == '<')
		{
			i--;
			j = i;
			while (tab[j--] == ' ')
				space_count++;
			if (space_count == 0)
			{
				ft_memmove(tab + i + 1, tab + i, ft_strlen(tab + i) + 3);
				tab[i + 1] = ' ';
			}
			if (space_count > 1)
				ft_memmove(tab + found_space(tab, 0), tab + i, ft_strlen(tab));
		}
	}
}

void	check_space_after(char *tab)
{
	int	i;
	int	j;
	int	space_count;

	i = -1;
	while (tab[++i])
	{
		space_count = 0;
		if (tab[i] == '>' || tab[i] == '<')
		{
			i++;
			if (tab[i] == '>' || tab[i] == '<')
				i++;
			j = i - 1;
			while (tab[++j] == ' ')
				space_count++;
			if (space_count == 0)
			{
				ft_memmove(tab + i + 1, tab + i, ft_strlen(tab + i) + 1);
				tab[i] = ' ';
			}
			if (space_count > 1)
				ft_memmove(tab + (i + 1), tab + j, ft_strlen(tab));
		}
	}
}

int	manage_in(char *tab, char *src, t_cmd *cmd, int i)
{
	char	*tmp;

	cmd->in = NULL;
	if (!cmd->in)
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[i + 2] = ' ';
		cmd->in = tmp;
		i += 2;
	}
	else
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[i + 2] = ' ';
		tmp = ft_strjoin(cmd->in, tmp);
		cmd->in = ft_strdup(tmp);
		i += 2;
	}
	check_space_after(cmd->in);
	return (i);
}

int	manage_out(char *tab, char *src, t_cmd *cmd, int i)
{
	char	*tmp;

	cmd->in = NULL;
	if (!cmd->in)
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[i + 2] = ' ';
		cmd->in = tmp;
		i += 2;
	}
	else
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[i + 2] = ' ';
		tmp = ft_strjoin(cmd->in, tmp);
		cmd->in = ft_strdup(tmp);
		i += 2;
	}
	check_space_after(cmd->in);
	return (i);
}

void	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;

	i = 1;
	j = 0;
	while (tab[i])
	{
		// if (tab[i][0] == '<')
		// 	i = manage_in(tab[i], tab[i + 1], cmd, i);
		// if (tab[i][0] == '>')
		// 	i = manage_out(tab[i], tab[i + 1], cmd, i);
		// else
		// {
			cmd->arg[j] = ft_strdup(tab[i]);
			j++;
			i++;
		// }
		// cmd->in[ft_strlen(cmd->in)] = '\0';
		// printf("%s\n", cmd-> in);
	}
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}



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
		print_tab(cmd->arg);
	}
}

void parsing(t_data *data)
{
	char	**tmp;
	// t_cmd	lst_tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->cmd = malloc(sizeof(t_cmd));
	tmp = ft_split(data->args, '|');
	// print_tab(tmp);
	while (tmp[i])
	{
		tri_cmd(tmp[i], data->cmd);
		j = 0;
		i++;
		// lst_tmp = *lst_tmp.next;
	}
}