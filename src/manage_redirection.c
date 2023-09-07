/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:45:53 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/07 20:28:27 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_space_before(char *tab)
{
	int		i;
	int		j;
	int		space_count;
	char	*tmp;

	i = ft_strlen(tab);
	tmp = tab;
	while (i > 0 && tmp[--i])
	{
		space_count = 0;
		if (tmp[i] == '>' || tmp[i] == '<' && i > 0)
		{
			i--;
			if (tmp[i] == '>' || tmp[i] == '<')
				i--;
			j = i;
			while (tmp[j--] == ' ')
				space_count++;
			if (space_count == 0)
			{
				ft_memmove(tmp + i + 1, tmp + i, ft_strlen(tmp + i) + 1);
				tmp[i + 1] = ' ';
				tab = ft_strdup(tmp);
			}
			if (space_count > 1)
			{
				ft_memmove(tmp + found_space(tmp, 0), tmp + i, ft_strlen(tmp));
				tab = ft_strdup(tmp);
			}
		}
	}
	// free(tmp);
}

char 	*ft_str_insert(char *str, char *insert, int index)
{
	char *tmp;
	int		i;
	int		strlen;

	strlen = ft_strlen(str) + ft_strlen(insert);
	tmp = malloc(sizeof(char) * (strlen + 1));
	tmp[strlen] = 0;
	ft_strlcpy(tmp, str, index + 1);
	ft_strlcpy(&tmp[index], insert, ft_strlen(insert) + 1);
	ft_strlcpy(&tmp[index + ft_strlen(insert)], &str[index], ft_strlen(&str[index]) + 1);
	return (tmp);
}

void	check_space_after(char *tab)
{
	int	i;
	int	j;
	char	*tmp;
	char	*tmp2;
	int	space_count;

	i = -1;
	tmp = tab;
	while (tmp[++i])
	{
		space_count = 0;
		if (tmp[i] == '>' || tmp[i] == '<')
		{
			i++;
			if (tmp[i] == '>' || tmp[i] == '<')
				i++;
			j = i - 1;
			while (tmp[++j] == ' ')
				space_count++;
			if (space_count == 0)
			{
				// tmp2 = ft_str_insert(tmp, " ", i);
				// free(tmp);
				// tmp = tmp2;
				ft_memmove(tmp + i + 1, tmp + i, ft_strlen(tmp + i) + 1);
				tmp[i] = ' ';
				tab = ft_strdup(tmp);
			}
			if (space_count > 1)
			{
				ft_memmove(tmp + (i + 1), tmp + j, ft_strlen(tmp));
				tab = ft_strdup(tmp);
			}
		}
	}
	// free(tmp);
}

int	manage_redirection(char *token, char *file, t_cmd *cmd, int i)
{
	t_dir	*tmp;
	
	tmp = init_dir(file);
	if (!tmp)
		return (0);
	if (!cmd->redirection)
		cmd->redirection = tmp;
	else
		add_back_dir(&cmd->redirection, tmp);
	if (token[1] && token[1] == '<')
		cmd->redirection->token = LESS_LESS;
	else if (token[1] && token[1] == '>')
		cmd->redirection->token = GREAT_GREAT;
	else if (token[0] == '<')
		cmd->redirection->token = LESS;
	else if (token[0] == '>')
		cmd->redirection->token = GREAT;
	// while (cmd->redirection)
	// {
	// 	printf("token = %d\nredirection = %s\n", cmd->redirection->token, cmd->redirection->file);
	// 	cmd->redirection = cmd->redirection->next;
	// }	
	return (1);
}
