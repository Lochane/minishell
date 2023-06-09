/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/10 01:05:50 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc

void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer)
{
	t_simple_cmd *tmp;
	int i;
	char **tab;
	int size;
	
	while (lexer->prev)
	{
		if (lexer->prev->token == 1)
			break ;
	 	lexer = lexer->prev;
	}
	i = 0;
	size = lstsize_lexer(lexer);
	tab = malloc(sizeof(char **) * (size + 1));
	while (lexer)
	{
		if (lexer->token == 1)
			break ;
		tab[i] = lexer->str;
		lexer = lexer->next;
		i++;
	}
	tab[i] = '\0';
	tmp = lstnew_simple_cmd(tab, size);
	add_back_simple_cmd(simple_cmd, tmp);
	free(tab);
}

void check_cmd(t_data *data)
{
	data->simple_cmd = NULL;
	if (data->lexer)
	{
		while (data->lexer->prev)
	 		data->lexer = data->lexer->prev;
	}
	while (data->lexer)
	{
		if (data->lexer->token == 1)
			copy_cmd(&data->simple_cmd, data->lexer);
		else if (data->lexer->next == NULL)
			copy_cmd(&data->simple_cmd, data->lexer);
		data->lexer = data->lexer->next;
	}
}