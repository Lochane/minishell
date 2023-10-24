/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:45:53 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/24 16:09:20 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_check_space_front(int i[2], char *tab, char **tab_cpy, char **tmp)
{
	i[0] = ft_strlen(tab);
	*tab_cpy = tab;
	*tmp = NULL;
}

char	*check_space_front(char *tab)
{
	int		i[2];
	int		space_count;
	char	*tmp;
	char	*tab_cpy;

	init_check_space_front(i, tab, &tab_cpy, &tmp);
	while (i[0] > 0 && tab[--(i[0])])
	{
		space_count = 0;
		if ((tab[i[0]] == '>' || tab[i[0]] == '<') && i[0] > 0 && (i[0])--)
		{
			if (tab[i[0]] == '>' || tab[i[0]] == '<')
				(i[0])--;
			i[1] = i[0];
			while (i[1] > 0 && tab[(i[1])--] == ' ')
				space_count++;
			if (tab != tab_cpy)
				tmp = tab;
			if (i[0] > 0)
				tab = manage_space_front(i[0], tab, space_count);
			if (tmp && tab != tmp)
				free(tmp);
		}
	}
	return (tab);
}

void	init_check_space_back(char **tab_cpy, char **tmp, char *tab, int *i)
{
	*tab_cpy = tab;
	*tmp = NULL;
	*i = -1;
}

char	*check_space_back(char *tab)
{
	int		i;
	int		j;
	int		space_count;
	char	*tmp;
	char	*tab_cpy;

	init_check_space_back(&tab_cpy, &tmp, tab, &i);
	while (tab[++i])
	{
		space_count = 0;
		if ((tab[i] == '>' || tab[i] == '<') && i++)
		{
			if (tab[i] == '>' || tab[i] == '<')
				i++;
			j = i - 1;
			while (tab[++j] == ' ')
				space_count++;
			if (tab != tab_cpy)
				tmp = tab;
			tab = manage_space_back(i, tab, space_count, j);
			if (tmp && tab != tmp)
				free(tmp);
		}
	}
	return (tab);
}

int	manage_redirection(char *token, char *file, t_cmd *cmd)
{
	t_dir	*tmp;

	tmp = init_dir(file);
	if (!tmp)
		return (fail_malloc(), 0);
	if (token[0] == '<' && token[1] == '>')
		tmp->token = DOUBLE;
	else if (token[1] && token[1] == '<')
	{
		tmp->token = LESS_LESS;
		tmp->fd = get_infile_heredoc(tmp->file);
		if (g_g == 130)
			return (0);
	}
	else if (token[1] && token[1] == '>')
		tmp->token = GREAT_GREAT;
	else if (token[0] == '<')
		tmp->token = LESS;
	else if (token[0] == '>')
		tmp->token = GREAT;
	if (!cmd->redirection)
		cmd->redirection = tmp;
	else
		add_back_dir(&cmd->redirection, tmp);
	return (1);
}
