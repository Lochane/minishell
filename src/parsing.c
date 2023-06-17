/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/18 01:33:58 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

char *remove_space(char *start, char *end)
{
	char *tmp;
	size_t length;

	tmp = end;
    length = ft_strlen(end + 1) + 1;
    ft_memmove(start + 1, end + 1, length);
	ft_strlcat(start, tmp, ft_strlen(start) + length);
	return(start);
}

char	*manage_space(char *tab)
{
	int	i;
	int	j;
	int	space_count;

	i = 0;
	space_count = 0;
	while (tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			// gerer espace avant le chevron
			if (tab[i + 1] == '>' || tab[i + 1] == '<')
				i += 2;
			j = i;
			while (tab[j] == ' ')
			{
				space_count++;
				j++;
			}
			// if (space_count == 0)
			// 	add_space(tab + i);
			if (space_count > 1)
				remove_space(tab + i, tab + j);
				
		}
		i++;
	}
	printf("%s\n", tab);
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

	// tab = manage_space(tab);
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