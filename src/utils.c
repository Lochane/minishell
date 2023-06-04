/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/04 15:04:58 by lochane          ###   ########.fr       */
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
		// printf("%s", data->str);
		data = data->next;
	}
	printf("\n");
}

void	print_tab(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}