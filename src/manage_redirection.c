/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:45:53 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/27 14:24:24 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

void	check_space_before(char *tab)
{
	int	i;
	int	j;
	int	space_count;

	i = ft_strlen(tab);
	while (i > 0 && tab[--i])
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
				ft_memmove(tab + i + 1, tab + i, ft_strlen(tab + i) + 1);
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

	if (!cmd->in)
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[ft_strlen(tmp)] = ' ';
		cmd->in = tmp;
		i += 2;
	}
	else
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[ft_strlen(tmp)] = ' ';
		tmp = ft_strjoin(cmd->in, tmp);
		cmd->in = ft_strdup(tmp);
		i += 2;
	}
	check_space_after(cmd->in);
	cmd->in[ft_strlen(cmd->in)] = '\0';
	free(tmp);
	return (i);
}

int	manage_out(char *tab, char *src, t_cmd *cmd, int i)
{
	char	*tmp;
	char	*new_tmp;

	if (!cmd->out)
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[ft_strlen(tmp)] = ' ';
		cmd->out = tmp;
		i += 2;
	}
	else
	{
		tmp = ft_strjoin_shell(tab, src, 1);
		tmp[ft_strlen(tmp)] = ' ';
		tmp = ft_strjoin(cmd->out, tmp);
		cmd->out = ft_strdup(tmp);
		i += 2;
	}
	check_space_after(cmd->out);
	cmd->out[ft_strlen(cmd->out)] = '\0';
	return (i);
}
