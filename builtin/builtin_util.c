/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:30:27 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/28 23:30:33 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_var_cmp(char *s1, int size, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s1[i] != '=') && s1[i] == s2[i] && i < size)
		i++;
	if ((!s1[i] || !ft_isalnum(s1[i])) && (!s2[i] || s2[i] == '='))
		return (0);
	else
		return (1);
}

char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_var_cmp(var, size, tmp->data) && tmp->is_env)
		{
			if (lst)
				*lst = tmp;
			return (&tmp->data[tmp->size + 1]);
		}
		tmp = tmp->next;
	}
	if (lst)
		*lst = NULL;
	return (NULL);
}
