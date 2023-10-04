/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:45:53 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/03 15:31:16 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_space_front(char *tab)
{
	int		i;
	int		j;
	int		space_count;

	i = ft_strlen(tab);
	while (i > 0 && tab[--i])
	{
		space_count = 0;
		if ((tab[i] == '>' || tab[i] == '<') && i > 0)
		{
			i--;
			if (tab[i] == '>' || tab[i] == '<')
				i--;
			j = i;
			while (j > 0 && tab[j--] == ' ')
				space_count++;
			tab = manage_space_front(i, tab, space_count);
		}
	}
	return (tab);
}

char	*check_space_back(char *tab)
{
	int		i;
	int		j;
	int		space_count;

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
			tab = manage_space_back(i, tab, space_count, j);
		}
	}
	return (tab);
}

int	manage_redirection(char *token, char *file, t_cmd *cmd)
{
	t_dir	*tmp;

	tmp = init_dir(file);
	if (!tmp)
		return (0);
	if (token[0] == '<' && token[1] == '>')
		tmp->token = DOUBLE;
	else if (token[1] && token[1] == '<')
	{
		tmp->token = LESS_LESS;
		tmp->fd = get_infile_heredoc(tmp->file);
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