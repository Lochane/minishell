/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/04 15:23:07 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer)
{
	t_simple_cmd *tmp;
	int i;
	char **tab;
	
	i = 0;
	tab = malloc(sizeof(char) * lstsize_lexer(lexer));
	// while (lexer->prev || lexer->prev->token != '1')
	// 	lexer = lexer->prev;
	while (lexer)
	{
		tab[i] = lexer->str;
		i++;
	}
	tmp = lstnew_simple_cmd(tab);
	// print_lst(tmp);
	add_back_simple_cmd(simple_cmd, tmp);
	// print_lst((*simple_cmd));

	free(tab);
}

void check_cmd(t_data *data)
{
	data->simple_cmd = NULL;
	// while (data->lexer->prev)
	// 	data->lexer = data->lexer->prev;
	while (data->lexer)
	{
		// if (data->lexer->token != '1')
			copy_cmd(&data->simple_cmd, data->lexer);
		data->lexer = data->lexer->next;
	}
	// print_lst(data->simple_cmd);
	
}