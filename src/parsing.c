/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/12 18:10:41 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc et gerer effacement de redirection



void	check_redirection(t_lexer **redirection, t_lexer *lexer)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	redirection = malloc(sizeof(t_lexer));
	while (lexer)
	{
		if (lexer->token > 1)
		{
			tmp = ft_lstnew_lexer(lexer->str);
			tmp->token = lexer->token;
			ft_add_back_lexer(redirection, tmp);
			tmp = ft_lstnew_lexer(lexer->next->str);
			ft_add_back_lexer(redirection, tmp);
			if (lexer->next->next)
			{
				lexer_remove_two_nodes(&lexer);
			}
			else
			{
				lexer = NULL;
				break ;
			}
		}
		else
			lexer = lexer->next;
	}
	// while (lexer)
	// 	lexer = lexer->prev;
}

void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer)
{
	t_simple_cmd	*tmp;
	int				i;
	char			**tab;
	int				size;

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
	tab[i] = NULL;
	tmp = lstnew_simple_cmd(tab, size);
	add_back_simple_cmd(simple_cmd, tmp);
	free(tab);
}

void	check_cmd(t_data *data)
{
	data->simple_cmd = NULL;
	if (data->lexer)
	{
		while (data->lexer->prev)
	 		data->lexer = data->lexer->prev;
	}
	check_redirection(&data->simple_cmd->redirections, data->lexer);
	print_lexer(data->lexer);
	while (data->lexer)
	{
		if (data->lexer->token == 1)
			copy_cmd(&data->simple_cmd, data->lexer);
		else if (data->lexer->next == NULL)
			copy_cmd(&data->simple_cmd, data->lexer);
		data->lexer = data->lexer->next;
	}
}