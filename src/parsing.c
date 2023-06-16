/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/16 20:41:42 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

char	**manage_space(char *tab)
{
	// si on croise '>>' '>' '<<' '<'
	// si il y a des espace alors on supprime pour qu'il en reste 1
	// si il y en a pas on en ajoute
	
}

void	get_arg(char **tab, t_cmd *cmd)
{
	int		j;
	int		i;

	i = 1;
	j = 0;
	while (tab[i])
	{
		// if ((tab[i][0] == '>' && !tab[i][1]) || (tab[i][0] == '>' && tab[i][1] == '>'))
		// {
		// 	if (!cmd->in)
				
		// }	
		cmd->arg[j] = ft_strdup(tab[i]);
		i++;
		j++;
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

	tab = manage_space(tab);
	tmp = ft_split(tab, ' ');
	size = tab_size(tmp);
	cmd->cmd = ft_strdup(tmp[0]);
	cmd->arg = malloc(sizeof(char **) * size - 1);
	if (tab[1])
	{
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
	tmp = ft_split(data->args, '|');
	// print_tab(tmp);
	while (tmp[i])
	{
		tri_cmd(tmp[i], &data->cmd);
		j = 0;
		i++;
		// lst_tmp = *lst_tmp.next;
	}
}