/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/14 12:15:36 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lexer(t_lexer *data)
{
	while (data)
	{
		printf("%s", data->str);
		data = data->next;
	}
	printf("\n");
}

void	print_simple_cmd(t_simple_cmd *data)
{
	while (data)
	{
		print_tab(data->str);
		printf("*********************\n");
		data = data->next;
	}
	printf("\n");
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