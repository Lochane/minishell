/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/27 14:10:22 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free_tab(char **res, size_t i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (NULL);
}

void	print_tab(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}