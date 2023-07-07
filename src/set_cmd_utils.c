/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:40:19 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/06 15:20:11 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_space(char *tab, int allow)
{
	int	i;

	i = 0;
	while (tab[i] != ' ' && allow == 0)
		i++;
	return (i);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strjoin_shell(char const *s1, char const *s2, int j)
{
	char	*res;
	int		s1_size;
	int		s2_size;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	res = malloc(sizeof(char) * s1_size + s2_size + (1 + j));
	if (!res)
		return (0);
	ft_memcpy(res, s1, s1_size);
	while (s2[i])
	{
		res[s1_size + i] = s2[i];
		i++;
	}
	res[s1_size + i] = '\0';
	return (res);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->arg = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}