/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/07 02:00:37 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer)
{
	t_simple_cmd *tmp;
	int i;
	char **tab;
	int size;
	
	i = 0;
	size = lstsize_lexer(lexer);
	tab = malloc(sizeof(char **) * (size + 1));
	while (lexer->prev)
	 	lexer = lexer->prev;
	while (lexer)
	{
		tab[i] = lexer->str;
		lexer = lexer->next;
		i++;
	}
	tab[i] = '\0';
	//print_tab(tab);
	tmp = lstnew_simple_cmd(tab, size);
	// print_lst(tmp);
	add_back_simple_cmd(simple_cmd, tmp);
	//print_simple_cmd((*simple_cmd));

	free(tab);
}

void check_cmd(t_data *data)
{
	data->simple_cmd = NULL;
	if (!data->lexer->str)
		return ;
	print_lexer(data->lexer);
	//printf("lol");
	while (data->lexer->prev)
		data->lexer = data->lexer->prev;
	while (data->lexer)
	{
		if (data->lexer->token == '1' || !data->lexer->next)
			copy_cmd(&data->simple_cmd, data->lexer);
		data->lexer = data->lexer->next;
	}
	// print_lst(data->simple_cmd);
}